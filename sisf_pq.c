#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <math.h>
#include <mkl.h>

double WrapPBC(double x)
{
    if (x > 0.5)
        --x;
    else if (x < -0.5)
        ++x;

    return x;
}

int main(int argc, char **argv)
{
    FILE *fp_in, *fp_out;
    int Natom, Nstep;           /* number of atoms, totel steps,    */
    double timestep;            /* and timestep in dump file        */

    int Nfreq, Nevery, Nrepeat; /* choose t0 every Nfreq steps      */
    int Nstart;                 /* perform sampling at intervals of */
    int *start, *sample;        /* Nevery steps and repeated M times*/

    double rcut1, rcut2;        /* lower and upper truncate radius  */
    int *N_neigh, **l_neigh;    /* to build neighbor list           */
    int N_pair, max_neigh;

    double **r, **r_ref, **box; /* configuration                    */
    double tmp[3], *dr, *dr_sum;/* and configuration at current step*/
    double qmax, qmax_2;
    int type;

    int iatom, jatom, itype;    /* some other variables             */
    int istep, jstep, i, j, k;
    double tmp0, tmp1, tmp2;
    char **buff, *token;
    double *sisf, *sisf_p, *sisf_q;

    /* read configure file */
    fp_in = fopen("sisf.conf", "r");
    fscanf(fp_in, "dumpfile     %s\n", &token);
    fscanf(fp_in, "Natom        %d\n", &Natom);
    fscanf(fp_in, "Nstep        %d\n", &Nstep);
    fscanf(fp_in, "type         %d\n", &type);
    fscanf(fp_in, "timestep     %lf\n", &timestep);
    fscanf(fp_in, "Nfreq        %d\n", &Nfreq);
    fscanf(fp_in, "Nevery       %d\n", &Nevery);
    fscanf(fp_in, "Nrepeat      %d\n", &Nrepeat);
    fscanf(fp_in, "Rcut1        %lf\n", &rcut1);
    fscanf(fp_in, "Rcut2        %lf\n", &rcut2);
    fscanf(fp_in, "qmax         %lf\n", &qmax);
    fclose(fp_in);
    fp_in = fopen(token, "r");

    /* initialize parameters and arrays */
    rcut1 *= rcut1;
    rcut2 *= rcut2;
    qmax /= sqrt(3);
    qmax_2 = qmax * 0.5;
    N_pair = 0;
    max_neigh = 60;

    Nstart = (Nstep - Nrepeat * Nevery) / Nfreq;
    start = (int *)malloc(Nstart * sizeof(int));
    for (i = 0; i < Nstart; ++i)
        start[i] = (i + 1) * Nfreq;
    sample = (int *)malloc(Nrepeat * sizeof(int));
    sisf = (double *)calloc(Nrepeat, sizeof(double));
    sisf_p = (double *)calloc(Nrepeat, sizeof(double));
    sisf_q = (double *)calloc(Nrepeat, sizeof(double));
    for (i = 0; i < Nrepeat; ++i)
        sample[i] = (i + 1) * Nevery;
    
    r = (double **)malloc((Nstep + 1) * sizeof(double));
    box = (double **)malloc((Nstep + 1) * sizeof(double));
    for (i = 0; i < Nstep + 1; ++i)
    {
        r[i] = (double *)malloc(3 * Natom * sizeof(double));
        box[i] = (double *)malloc(3 * sizeof(double));
    }

    r_ref = (double **)malloc(Nstart * sizeof(double *));
    for (i = 0; i < Nstart; ++i)
        r_ref = (double *)malloc(3 * Natom * sizeof(double));
    dr = (double *)malloc(3 * Natom * sizeof(double));
    dr_sum = (double *)malloc(Natom * sizeof(double));

    N_neigh = (int *)calloc(Natom, sizeof(int));
    l_neigh = (int **)malloc(Natom * sizeof(int *));
    for (iatom = 0; iatom < Natom; ++iatom)
        l_neigh[iatom] = (int *)malloc(max_neigh * sizeof(int));

    buff = (char **)malloc((9 + Natom) * sizeof(char *));
    for (i = 0; i < 9 + Natom; ++i)
        buff[i] = (char *)malloc(256 * sizeof(double));

    /* read dump file                   */
    for (istep = 0; istep < Nstep + 1; ++istep)
    {
        for (i = 0; i < 9 + Natom; ++i)
            fgets(buff[i], 256, fp_in);
        
        /* get information of box           */
        for (i = 0; i < 3; ++i)
        {
            tmp0 = atof(strtok(buff[5 + i], " "));
            tmp1 = atof(strtok(NULL, " "));
            box[istep][i] = atof(strtok(buff[5 + i], " "));
        }

        /* read coordinate                  */
        for (iatom = 0; iatom < Natom; ++iatom)
        {
            itype = atoi(strtok(buff[9 + iatom], " "));
            r[istep][3 * iatom] = atof(strtok(NULL, " "));
            r[istep][3 * iatom + 1] = atof(strtok(NULL, " "));
            r[istep][3 * iatom + 2] = atof(strtok(NULL, " "));
        }
    }

    /* build neighbor list              */
    #pragma omp parallel for schedule(dynamic) \
            firstprivate(rcut1, rcut2, Natom) \
            private(jatom, tmp0, tmp1, tmp2)
    for (iatom = 0; iatom < Natom; ++iatom)
    {
        for (jatom = 0; jatom < Natom; ++jatom)
        {
            tmp0 = r[0][3 * iatom] - r[0][3 * jatom];
            tmp1 = r[0][3 * iatom + 1] - r[0][3 * jatom + 1];
            tmp2 = r[0][3 * iatom + 2] - r[0][3 * jatom + 2];

            tmp0 = box[0][0] * WrapPBC(tmp0);
            tmp1 = box[0][1] * WrapPBC(tmp0);
            tmp2 = box[0][2] * WrapPBC(tmp0);

            tmp0 *= tmp0;
            tmp0 += tmp1 * tmp1 + tmp2 * tmp2;
            if (tmp0 < rcut1 || tmp0 > rcut2)
                continue;

            l_neigh[N_neigh[iatom]] = jatom;
            ++N_neigh[iatom];
        }
    }

    /* total number of atom pairs       */
    for (iatom = 0; iatom < Natom; ++iatom)
        N_pair += N_neigh[iatom];
    printf("Total number of atom pairs: %d\n", N_pair);

    for (i = 0; i < Nstart; ++i)
    {
        t0 = i * Nfreq;
        for (j = 0; j < Nrepeat; ++j)
        {
            t1 = t0 + j * Nevery;

            /* displacement of atoms                */
            vdSub(r[t0], r[t1], 3 * Natom, dr);
            #pragma omp parallel for schedule(dynamic) firstprivate(t1)
            for (iatom = 0; iatom < Natom; ++iatom)
            {
                dr[3 * iatom] = box[t1][0] * WrapPBC(dr[3 * iatom]);
                dr[3 * iatom + 1] = box[t1][1] * WrapPBC(dr[3 * iatom + 1]);
                dr[3 * iatom + 2] = box[t1][2] * WrapPBC(dr[3 * iatom + 2]);
                dr_sum[iatom] = dr[3 * iatom] + dr[3 * iatom + 1] + dr[3 * iatom + 2];
            }
        }
    
        /* compute atom pairs in neighbor list  */
        /* P = (r_1 + r_2) / 2
        Q = (r_1 - r_2) / 2 */
        tmp0 = tmp1 = tmp2 = 0;
        #pragma omp parallel for schedule(dynamic) \
                firstprivate(qmax, qmax_2) private(k, jatom) \
                reduction(+ : tmp0, tmp1, tmp2) 
        for (iatom = 0; iatom < Natom; ++iatom)
        {
            tmp0 += cos(qmax * dr_sum[iatom]);
            for (k = 0; k < N_neigh[iatom]; ++k)
            {
                jatom = l_neigh[k];
                tmp1 += cos(qmax_2 * (dr_sum[iatom] + dr_sum[jatom]));
                tmp2 += cos(qmax_2 * (dr_sum[iatom] - dr_sum[jatom]));
            }
        }
        sisf[j] += tmp0;
        sisf_p[j] += tmp1;
        sisf_q[j] += tmp2;
    }
        

    /* output                           */
    fp_out = fopen("sisf.dat", "w");
    fprintf(fp_out, "# t  self  P  Q\n");
    double norm1 = 1. / (Natom * Nstart), norm2 = 1. / (N_pair * Nstart);
    for (i = 0; i < Nrepeat; ++i)
    {
        fprintf(fp_out, "%.3f  %lf  %lf  %lf\n",
                sample[i] * timestep,
                sisf[i] * norm1,
                sisf_p[i] * norm2,
                sisf_q[i] * norm2);
    }

    return 0;
}
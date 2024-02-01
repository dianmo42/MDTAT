#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <math.h>

#define LOOPALL for (iatom = 0; iatom < Natom; ++iatom)

int main(int argc, char **argv)
{
    FILE *fp_in, *fp_out;
    int Natom, Nstep;                   /* number of atoms, totel steps,    */
    double timestep;                    /* and timestep in dump file        */

    int Nfreq, Nevery, Nrepeat;         /* choose t0 every Nfreq steps      */
    int Nstart;                         /* perform sampling at intervals of */
    int *sample;                        /* Nevery steps and repeated M times*/

    double rcut1, rcut2;                /* lower and upper truncate radius  */
    int *N_neigh, **l_neigh;            /* to build neighbor list           */
    int max_neigh = 60;

    double **r_ref, *r_cur;             /* reference configuration at t0    */
    double box[3], tmp[3], *dr;         /* and configuration at current step*/
    double qmax;
    int type;

    int iatom, jatom, itype;            /* some other variables             */
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
    qmax /= 2 * sqrt(3);

    Nstart = (Nstep - Nrepeat * Nevery) / Nfreq;
    r_ref = (double **)malloc(Nstart * sizeof(double *));
    for (i = 0; i < Nstart; ++i)
        r_ref = (double *)malloc(3 * Natom * sizeof(double));
    dr = (double *)malloc(3 * Natom * sizeof(double));
    r_cur = (double *)malloc(3 * Natom * sizeof(double));

    N_neigh = (int *)malloc(Natom * sizeof(int));
    l_neigh = (int **)malloc(Natom * sizeof(int *));
    LOOPALL l_neigh[iatom] = (int *)malloc(max_neigh * sizeof(int));

    buff = (char **)malloc((9 + Natom) * sizeof(char *));
    for (i = 0; i < 9 + Natom; ++i)
        buff[i] = (char *)malloc(256 * sizeof(double));
    
    /* read first step                  */
    for (i = 0; i < 9 + Natom; ++i)
        fgets(buff[i], 256, fp_in);
    /* information of box               */
    for (i = 0; i < 3; ++i)
    {
        tmp[0] = strtok(buff[5 + i], " ");
        tmp[1] = strtok(NULL, " ");
        box[i] = tmp[1] - tmp[0];
    }
    /* read coordinate                  */
    LOOPALL
    {
        itype = atoi(strtok(buff[9 + iatom], " "));
        r_ref[0][iatom] = atof(strtok(NULL, " "));
        r_ref[0][iatom + 1] = atof(strtok(NULL, " "));
        r_ref[0][iatom + 2] = atof(strtok(NULL, " "));
    }
    /* build neighbor list */
    #pragma omp parallel for firstprivate(rcut1, rcut2, box) private(jatom, tmp)
    LOOPALL
    {
        for (jatom = 0; jatom < Natom; ++jatom)
        {
            tmp[0] = r_ref[0][iatom] - r_ref[0][jatom];
            tmp[1] = r_ref[0][iatom + 1] - r_ref[0][jatom + 1];
            tmp[2] = r_ref[0][iatom + 2] - r_ref[0][jatom + 2];
            if (tmp[0] > 0.5) --tmp[0];
            else if (tmp[0] < -0.5) ++tmp[0];
            if (tmp[1] > 0.5) --tmp[1];
            else if (tmp[1] < -0.5) ++tmp[1];
            if (tmp[2] > 0.5) --tmp[2];
            else if (tmp[2] < -0.5) ++tmp[2];
        }
    }

}
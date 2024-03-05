/* Initialization for program   */

#include "mdtat.h"
#include "functions.h"

int Natom, Nstep;
int MaxSample, Nevery, Ncount, Nfreq, Nrepeat;
char **dump_buff;
double *r_cur, **r_ref, *box_cur, **box_ref;
double **dr;

double norm_atom, norm_count;

/* Read preset parameters       */
void ReadPara()
{
    FILE *fp_in = OpenFile("TAT.md", "r");
    char *buff, token[256];
    
    /* ========================
     *           TODO
     *      read parameters
     * ========================
     * */
    fgets(buff, 256, fp_in);


    return;
}

void AllocMem()
{
    dump_buff = (char **)malloc((Natom + 9) * sizeof(char *));
    for (int i = 0; i < Natom + 9; ++i)
        dump_buff[i] = (char *)malloc(256 * sizeof(char));
    
    Ncount = (Nstep - MaxSample) / Nfreq;
    r_cur = (double *)malloc(Dimension * Natom * sizeof(double));
    box_cur = (double *)malloc(Dimension * sizeof(double));
    dr = (double *)malloc(Dimension * Natom * sizeof(double));

    r_ref = (double **)malloc(Ncount * sizeof(double *));
    box_ref = (double **)malloc(Ncount * sizeof(double *));
    for (int i = 0; i < Ncount; ++i)
    {
        r_ref[i] = (double *)malloc(Dimension * Natom * sizeof(double));
        box_ref[i] = (double *)malloc(Dimension * sizeof(double));
    }

    /* ======================
     *         TODO
     * correlation functions
     * ======================
     * */

    norm_atom = 1. / Natom;
    norm_count = 1. / Ncount;
    return;
}
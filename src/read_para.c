/* Initialization for program   */

#include "mdtat.h"
#include "functions.h"

#include <stdlib.h>

int Natom, Nstep;
double dt;
int max_sample, Nevery, Ncount, Nfreq, Nrepeat;
char **dump_buff;
double *r_cur, **r_ref, *box_cur, **box_ref;
double *dr;
double qmax;
int imsd, isisf;
double *msd, *sisf;
double *ngp, *chi4;
double norm_atom, norm_count;

char **buff, *dump_file;

/* Read preset parameters       */
void ReadPara()
{
    dump_file = (char *)malloc(256 * sizeof(char));
    
    FILE *fp_in = OpenFile("TAT.in", "r");
    fscanf(fp_in, "%s #%*[^\n]\n", dump_file);
    fscanf(fp_in, "%d #%*[^\n]\n", &Natom);
    fscanf(fp_in, "%d #%*[^\n]\n", &Nstep);
    fscanf(fp_in, "%lf #%*[^\n]\n", &dt);
    fscanf(fp_in, "%d #%*[^\n]\n", &Nfreq);
    fscanf(fp_in, "%d #%*[^\n]\n", &Nevery);
    fscanf(fp_in, "%d #%*[^\n]\n", &Nrepeat);
    fscanf(fp_in, "%d #%*[^\n]\n", &imsd);
    fscanf(fp_in, "%d #%*[^\n]\n", &isisf);
    fscanf(fp_in, "%lf #%*[^\n]\n", &qmax);
    fclose(fp_in);

    return;
}

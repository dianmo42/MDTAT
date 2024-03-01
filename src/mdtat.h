#ifndef _MDTAT_H
#define _MDTAT_H

#include <stdio.h>

#define Dimension   3

FILE *fp_in, *fp_out;

extern int Natom, Nstep;
extern int MaxSample, Nevery, Ncount, Nfreq, Nrepeat;
extern char **dump_buff;
extern double *r_cur, **r_ref, *box_cur, **box_ref;
extern double **dr;

extern char **buff;

#endif
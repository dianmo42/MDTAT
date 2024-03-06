#ifndef _MDTAT_H
#define _MDTAT_H

#include <stdio.h>

#define Dimension   3

extern FILE *fp_out;

extern int Natom, Nstep;
extern double dt;
extern int max_sample, Nevery, Ncount, Nfreq, Nrepeat;
extern char **dump_buff;
extern double *r_cur, **r_ref, *box_cur, **box_ref;
extern double *dr;
extern double qmax;
extern int imsd, isisf;
extern double *msd, *sisf;
extern double *ngp, *chi4;
extern double norm_atom, norm_count;

extern char **buff, *dump_file;

#endif
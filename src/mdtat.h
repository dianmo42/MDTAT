#ifndef _MDTAT_H
#define _MDTAT_H

#include <stdio.h>

#define Dimension   3

FILE *fp_in, *fp_out;

extern int Natom, Nstep;

extern double *r_cur, **r_ref;
extern double **dr;

#endif
/* allocate memory */

#include "mdtat.h"
#include "functions.h"

#include <stdlib.h>
#include <string.h>

#include <math.h>

void AllocMem()
{
    dump_buff = (char **)malloc((Natom + 9) * sizeof(char *));
    for (int i = 0; i < Natom + 9; ++i)
        dump_buff[i] = (char *)malloc(256 * sizeof(char));
    
    max_sample = Nrepeat * Nevery;
    Ncount = (Nstep - max_sample) / Nfreq + 1;
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

    msd = (double *)calloc(Nrepeat, sizeof(double));
    ngp = (double *)calloc(Nrepeat, sizeof(double));
    sisf = (double *)calloc(Nrepeat, sizeof(double));
    chi4 = (double *)calloc(Nrepeat, sizeof(double));
    
    qmax /= sqrt(3.);
    norm_atom = 1. / Natom;
    norm_count = 1. / Ncount;

    return;
}
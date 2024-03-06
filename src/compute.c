/* compute correlation functions */

#include "mdtat.h"
#include "functions.h"

#include <mkl.h>
#include <omp.h>
#include <math.h>

void Compute(int i_ref, int t)
{
    vdSub(Dimension * Natom, r_ref[i_ref], r_cur, dr);

#pragma omp parallel for
    for (int i = 0; i < Natom; ++i)
    {
        for (int j = 0; j < Dimension; ++j)
        {
            if (dr[i * Dimension + j] > 0.5)
                --dr[i * Dimension + j];
            else if (dr[i * Dimension + j] < -0.5)
                ++dr[i * Dimension + j];
            
            dr[i * Dimension + j] *= box_cur[j];
        }
    }

    if (imsd)
        Compute_MSD(t);
    if (isisf)
        Compute_SISF(t);

    return;
}




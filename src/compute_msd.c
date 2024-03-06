/* mean-squared displacement */

#include "mdtat.h"
#include "functions.h"

#include <omp.h>
#include <math.h>

void Compute_MSD(int t)
{
    double dr2 = 0, dr4 = 0, tmp;

#pragma omp parallel for private(tmp) reduction(+ : dr2, dr4)
    for (int iatom = 0; iatom < Natom; ++iatom)
    {
        tmp = 0;
        for (int i = 0; i < Dimension; ++i)
        {
            tmp += dr[3 * iatom + i] * dr[3 * iatom + i];
        }
        dr2 += tmp;
        dr4 += tmp * tmp;
    }

    dr2 *= norm_atom;
    dr4 *= norm_atom;
    msd[t - 1] += dr2;
    ngp[t - 1] += Dimension * dr4 / ((Dimension + 2) * dr2 * dr2) - 1;

    return;
}
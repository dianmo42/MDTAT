/* self-intermediate scattering function */

#include "mdtat.h"
#include "functions.h"

#include <omp.h>
#include <math.h>

void Compute_SISF(int t)
{
    double tmp = 0;

#pragma omp parallel for reduction(+ : tmp)
    for (int iatom = 0; iatom < Natom; ++iatom)
    {
        double dr_sum = 0;
        for (int i = 0; i < Dimension; ++i)
        {
            dr_sum += dr[Dimension * iatom + i];
        }
        tmp += cos(qmax * dr_sum);
    }
    
    tmp *= norm_atom;
    sisf[t - 1] += tmp;
    chi4[t - 1] += tmp * tmp;

    return;
}

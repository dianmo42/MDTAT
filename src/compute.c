/* compute correlation functions */

#include "mdtat.h"

#include <math.h>
#include <mkl.h>

void compute_msd(int t);
void compute_sisf(int t);

void compute(int i_ref, int i_gap)
{
    vdMul(Dimension * Natom, r_ref[i_ref], r_cur, dr);

#pragma omp parallel for
    for (int i = 0; i < Dimension * Natom; ++i)
    {
        if (dr[i] > 0.5)
            --dr[i];
        else if (dr[i] < -0.5)
            ++dr[i];
    }

    int t = i_gap / Nevery;
    if (imsd)
        compute_msd(t);
    if (isisf)
        compute_sisf(t);

    return;
}

void compute_msd(int t)
{
    double dr2 = 0, dr4 = 0;

#pragma omp parallel for reduction(+ : dr2, dr4)
    for (int iatom = 0; iatom < Natom; ++iatom)
    {
        double tmp = 0;
        for (int i = 0; i < Dimension; ++i)
        {
            tmp += dr[3 * iatom + i] * dr[3 * iatom + i];
        }
        dr2 += tmp;
        dr4 += tmp * tmp;
    }

    dr2 *= norm_atom;
    dr4 *= norm_atom;
    msd[t] += dr2;
    ngp[t] += Dimension * dr2 / ((Dimension + 2) * dr2 * dr2) - 1;

    return;
}

void compute_sisf(int t)
{
    double tmp = 0;

#pragma omp parallel for private(dr_sum) reduction(+ : tmp)
    for (int iatom = 0; iatom < Natom; ++iatom)
    {
        double dr_sum = 0;
        for (int i = 0; i < Dimension; ++i)
        {
            dr_sum += dr[3 * iatom + i];
        }
        tmp += cos(qmax * dr_sum);
    }
    
    tmp *= norm_atom;
    sisf[t] += tmp;
    chi4[t] += tmp * tmp;

    return;
}

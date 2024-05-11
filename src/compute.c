#include "mdtat.h"

#include <math.h>
#include <omp.h>

void Compute(int t0, int t)
{
    int i;
    int t1 = t0 + (t + 1) * Nevery;

    /* displacement of all atoms */
    #pragma omp parallel for schedule(dynamic)
    for (i = 0; i < Natom; ++i)
    {
        dr[i].x = atom[t0][i].x - atom[t1][i].x;
        dr[i].y = atom[t0][i].y - atom[t1][i].y;
        dr[i].z = atom[t0][i].z - atom[t1][i].z;
    }
    
    /* mean-squared displacement */
    double MSD_tmp = 0;
    double NGP_tmp = 0;
    #pragma omp parallel for schedule(dynamic) reduction(+ : MSD_tmp, NGP_tmp)
    for (i = 0; i < Natom; ++i)
    {
        double tmp = dr[i].x * dr[i].x + dr[i].y * dr[i].y + dr[i].z * dr[i].z;
        MSD_tmp += tmp;
        NGP_tmp += tmp * tmp;
    }
    MSD[t] += MSD_tmp;
    NGP[t] += NGP_tmp;

    /* self-intermediate scattering function */
    double SISF_tmp = 0;
    #pragma omp parallel for schedule(dynamic) reduction(+ : SISF_tmp)
    for (i = 0; i < Natom; ++i)
    {
        SISF_tmp += cos(qmax * (dr[i].x + dr[i].y + dr[i].z));
    }
    SISF_tmp /= Natom;
    SISF[t] += SISF_tmp;
    Xhi4[t] += SISF_tmp * SISF_tmp;

    return;
}
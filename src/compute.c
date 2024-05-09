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
    double MSD_tmp;
    for (i = 0; i < Natom; ++i)
    {
        MSD_tmp = dr[i].x * dr[i].x + dr[i].y * dr[i].y + dr[i].z * dr[i].z;
        MSD[t] += MSD_tmp;
        NGP[t] += MSD_tmp * MSD_tmp;
    }

    /* self-intermediate scattering function */
    for (iatom = 0; iatom < Natom; ++iatom)
    {
        SISF_tmp = cos(q_max * (dr[iatom].x + dr[iatom].y + dr[iatom].z));
    }
    SISF_tmp /= Natom;
    SISF += SISF_tmp;
    Xhi4 += SISF_tmp * SISF_tmp;
}
#include "mdtat.h"

#include <math.h>
#include <omp.h>

void Compute()
{
    /* compute displacement of all atoms */
    for (iatom = 0; iatom < Natom; ++iatom)
    {
        dr[iatom].x = r1[iatom].x - r2[iatom].x;
        dr[iatom].y = r1[iatom].y - r2[iatom].y;
        dr[iatom].z = r1[iatom].z - r2[iatom].z;
    }
    
    /* mean-squared displacement */
    for (iatom = 0; iatom < Natom; ++iatom)
    {
        MSD_tmp = dr[iatom].x * dr[iatom].x \
                + dr[iatom].y * dr[iatom].y \
                + dr[iatom].z * dr[iatom].z;
        MSD += MSD_tmp;
        NGP += MSD_tmp * MSD_tmp;
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
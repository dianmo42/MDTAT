#include "mdtat.h"

#include <omp.h>

void Update_dr(int t0, int t1)
{
    #pragma omp parallel for schedule(dynamic)
    for (int i = 0; i < Natom; ++i)
    {
        dr[i].x = atom[t0][i].x - atom[t1][i].x;
        dr[i].y = atom[t0][i].y - atom[t1][i].y;
        dr[i].z = atom[t0][i].z - atom[t1][i].z;
    }

    return;
}
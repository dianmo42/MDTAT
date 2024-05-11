/* Molecular Dynamics Trajectory Analyzing Tool (MDTAT)
 * Post-processing of MD trajectories from LAMMPS simulations
 * Auther: dianmo
 * Email: dianmo42@outlook.com
 * */

#include "mdtat.h"

#include <stdio.h>

int main(int argc, char **argv)
{
    Args(argc, argv);
    Input();
    for (int i = 0; i < 4; ++i)
        fscanf(stdin, "%*[^\n]\n");
    fscanf(stdin, "%d\n", &Natom);
    rewind(stdin);
    AllocMem();
    ReadDump();

    int Ncount = 0;
    for (int t0 = 0; t0 < Nframe - Nrepeat * Nevery; t0 += Nfreq)
    {
        for (int t = 0; t < Nrepeat; ++t)
            Compute(t0, t);
        ++Ncount;
    }

    double norm = 1. / Ncount;
    for (int t = 0; t < Nrepeat; ++t)
    {
        MSD[t] *= norm;
        NGP[t] *= norm;
        SISF[t] *= norm;
        Xhi4[t] *= norm;
    }

    Output();

    return 0;
}
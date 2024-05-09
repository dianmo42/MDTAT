/* Molecular Dynamics Trajectory Analyzing Tool (MDTAT)
 * Post-processing of MD trajectories from LAMMPS simulations
 * Auther: dianmo
 * Email: dianmo42@outlook.com
 * */

#include "mdtat.h"
#include "functions.h"

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

    for (int t0 = 0; t0 < Nframe - Nrepeat * Nevery; t0 += Nfreq)
    {
        for (int t = 0; t < Nrepeat; ++t)
            Compute(t0, t);
    }

    Output();

    return 0;
}
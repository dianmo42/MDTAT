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
    CheckArgs(argc, argv);      /* input file */
    CheckInput(fn_in);          /* parameters */
    CheckDump(fn_dump);         /* format     */

    int iframe;
    int icomp;
    int iref;
    for (iframe = 0; iframe < Nframe; ++iframe)
    {
        ReadDump();
        
        iref = CheckFrame(iframe, 0);
        if (iref != -1)
            SaveDump(iref);

        icomp = CheckFrame(iframe, 1);
        if (icomp != -1)
            Compute(icomp);
    }

    Output();

    return 0;
}
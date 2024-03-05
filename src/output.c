/* output results */

#include "mdtat.h"
#include "functions.h"

#include <stdio.h>

void output()
{
    if (imsd)
    {
        FILE *fp = OpenFile("msd.dat", "w");
        fprintf(fp, "# t  MSD  NGP\n");
        for (int i = 1; i < Nrepeat; ++i)
        {
            fprintf(fp, "%.3f  %lf  %lf\n",
                    i * Nevery * dt,
                    msd[i] / Ncount,
                    ngp[i] / Ncount);
        }
        fclose(fp);
    }

    if (isisf)
    {
        FILE *fp = OpenFile("sisf.dat", "w");
        fprintf(fp, "# t  SISF  Chi4\n");
        for (int i = 1; i < Nrepeat; ++i)
        {
            sisf[i] /= Ncount;
            chi4[i] /= Ncount;
            chi4[i] -= sisf[i] * sisf[i];
            fprintf(fp, "%.3f  %lf  %lf\n",
                    i * Nevery * dt,
                    sisf[i],
                    chi4[i]);
        }
        fclose(fp);
    }

    return;
}
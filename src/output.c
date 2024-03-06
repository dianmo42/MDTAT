/* output results */

#include "mdtat.h"
#include "functions.h"

void Output()
{
    if (imsd)
    {
        FILE *fp = fopen("msd.dat", "w");
        fprintf(fp, "# t  MSD  NGP\n");
        for (int i = 0; i < Nrepeat; ++i)
        {
            fprintf(fp, "%.3f  %lf  %lf\n",
                    (i + 1) * Nevery * dt,
                    msd[i] / Ncount,
                    ngp[i] / Ncount);
        }
        fclose(fp);
    }

    if (isisf)
    {
        FILE *fp = fopen("sisf.dat", "w");
        fprintf(fp, "# t  SISF  Chi4\n");
        for (int i = 0; i < Nrepeat; ++i)
        {
            sisf[i] /= Ncount;
            chi4[i] /= Ncount;
            chi4[i] -= sisf[i] * sisf[i];
            fprintf(fp, "%.3f  %lf  %lf\n",
                    (i + 1) * Nevery * dt,
                    sisf[i],
                    chi4[i]);
            if (sisf[i] < 0.001)
                break;
        }
        fclose(fp);
    }

    return;
}
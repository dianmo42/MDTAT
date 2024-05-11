#include "mdtat.h"

#include <stdio.h>

void Output()
{
    FILE *fp = NULL;
    
    fp = fopen("msd.dat", "w");
    fprintf(fp, "t  MSD  NGP\n");
    for (int t = 0; t < Nrepeat; ++t)
        fprintf(fp, "%-10.3f  %-12.6f  %-12.6f\n", t * timestep, MSD[t], NGP[t]);
    fclose(fp);

    fp = fopen("sisf.dat", "w");
    fprintf(fp, "t  SISF  Xhi4\n");
    for (int t = 0; t < Nrepeat; ++t)
        fprintf(fp, "%-10.3f  %-12.6f  %-12.6f\n", t * timestep, SISF[t], Xhi4[t]);
    fclose(fp);

    return;
}
#include "mdtat.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ReadDump()
{
    int i, t, id;
    char buff[256], *token;
    double lo_tmp, hi_tmp;

    for (t = 0; t < Nframe; ++t)
    {
        for (i = 0; i < 5; ++i)
            fgets(buff, 256, stdin);

        fscanf(stdin, "%lf %lf\n", &lo_tmp, &hi_tmp);
        box[t].x = hi_tmp - lo_tmp;
        fscanf(stdin, "%lf %lf\n", &lo_tmp, &hi_tmp);
        box[t].y = hi_tmp - lo_tmp;
        fscanf(stdin, "%lf %lf\n", &lo_tmp, &hi_tmp);
        box[t].z = hi_tmp - lo_tmp;

        fgets(buff, 256, stdin);
        for (i = 0; i < Natom; ++i)
        {
            fgets(buff, 256, stdin);
            id = atoi(strtok(buff, " ")) - 1;
            atom[t][id].type = atoi(strtok(NULL, " "));
            atom[t][id].x = atof(strtok(NULL, " "));
            atom[t][id].y = atof(strtok(NULL, " "));
            atom[t][id].z = atof(strtok(NULL, " "));
        }
    }

    return;
}
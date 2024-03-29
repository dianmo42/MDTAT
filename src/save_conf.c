#include "mdtat.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void SaveConf(int current_step)
{
    static int check = -1;
    static double tmp1, tmp2;
    int i, j, type;

    if (check == current_step)
        return;

    for (int i = 0; i < Dimension; ++i)
    {
        tmp1 = atof(strtok(dump_buff[5 + i], " "));
        tmp2 = atof(strtok(NULL, " "));
        box_cur[i] = tmp2 - tmp1;
    }

    for (i = 0; i < Natom; ++i)
    {
        type = atoi(strtok(dump_buff[9 + i], " "));
        for (j = 0; j < Dimension; ++j)
        {
            // r_cur[i * Dimension + j] = atof(strtok(NULL, " "));
            r_cur[i * Dimension + j] = atof(strtok(NULL, " ")) / box_cur[j];
        }
    }

    check = current_step;

    return;
}

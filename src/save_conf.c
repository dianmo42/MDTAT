#include "mdtat.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void SaveConf(int current_step)
{
    static int check = -1;
    static double tmp1, tmp2;

    if (check == current_step)
        return;

    for (int i = 0; i < 3; ++i)
    {
        tmp1 = atof(strtok(dump_buff[5 + i], " "));
        tmp2 = atof(strtok(NULL, " "));
        box_cur[i] = tmp2 - tmp1;
    }

    for (int i = 0; i < Natom; ++i)
    {
        
    }
}
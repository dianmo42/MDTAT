#include "mdtat.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void CheckInput()
{
    char buff[256], *token, *comtype;
    int ok, id;

    while (1)
    {
        fgets(buff, 256, stdin);
        if (feof(stdin))
            break;
        if (buff[0] == '#')
            continue;
        
        token = strtok(buff, " ");
        /* information of dumpfile */
        if (strcmp(token, "dumpfile") == 0)
        {
            token = strtok(NULL, " ");
            strcpy(fn_dump, token, sizeof(token));
            continue;
        }
        if (strcmp(token, "Nframe") == 0)
        {
            token = strtok(NULL, " ");
            Nframe = atoi(token);
            continue;
        }

        /* parameters for analyzing */
        if (strcmp(token), "compute")
        {
            id = atoi(strtok(NULL, " "));
            comtype = strcpy(strtok(NULL, " "));
            doulbe ** #comtype_#id;
        }
    }
}
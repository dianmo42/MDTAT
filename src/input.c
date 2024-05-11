#include "mdtat.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int Natom, Nframe;
double timestep;
VecR *dr;
VecR *box;
Atom **atom;

int Nfreq, Nevery, Nrepeat;
double *MSD, *NGP;
double *SISF, *Xhi4, qmax;

void Input()
{
    char buff[256], *token;

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
            stdin = fopen(token, "r");
            continue;
        }
        if (strcmp(token, "Nframe") == 0)
        {
            token = strtok(NULL, " ");
            Nframe = atoi(token);
            continue;
        }
        if (strcmp(token, "timestep") == 0)
        {
            timestep = atof(strtok(NULL, " "));
            continue;
        }

        /* parameters for analyzing */
        if (strcmp(token, "Nfreq") == 0)
        {
            Nfreq = atoi(strtok(NULL, " "));
            continue;
        }
        if (strcmp(token, "Nevery") == 0)
        {
            Nevery = atoi(strtok(NULL, " "));
            continue;
        }
        if (strcmp(token, "Nrepeat") == 0)
        {
            Nrepeat = atoi(strtok(NULL, " "));
            continue;
        }
    }

    

    return;
}
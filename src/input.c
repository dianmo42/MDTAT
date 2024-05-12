#include "mdtat.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <math.h>

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
    char dumpfile[256];

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
            token = strtok(NULL, " \n");
            strcpy(dumpfile, token);
            continue;
        }
        if (strcmp(token, "Nframe") == 0)
        {
            token = strtok(NULL, " \n");
            Nframe = atoi(token) + 1;
            continue;
        }
        if (strcmp(token, "timestep") == 0)
        {
            timestep = atof(strtok(NULL, " \n"));
            continue;
        }

        /* parameters for analyzing */
        if (strcmp(token, "Nfreq") == 0)
        {
            Nfreq = atoi(strtok(NULL, " \n"));
            continue;
        }
        if (strcmp(token, "Nevery") == 0)
        {
            Nevery = atoi(strtok(NULL, " \n"));
            continue;
        }
        if (strcmp(token, "Nrepeat") == 0)
        {
            Nrepeat = atoi(strtok(NULL, " \n"));
            continue;
        }
        if (strcmp(token, "qmax") == 0)
        {
            qmax = atof(strtok(NULL, " \n")) / sqrt(3.);
            continue;
        }
    }

    stdin = fopen(dumpfile, "r");
    if (stdin == NULL)
    {
        fprintf(stderr, "Error!\nCan not open file '%s'!\n", dumpfile);
        exit(1);
    }

    return;
}
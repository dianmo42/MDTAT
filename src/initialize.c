/* Initialization for program   */

#include "mdtat.h"

int Natom, Nstep;

double *r_cur, **r_ref;
double **dr;

/* Read preset parameters       */
void ReadPara()
{
    char *buff, token[256];
    
    fp_in = fopen("para.md", "r");
    /*TODO*/
}

void AllocMem();

int Initialize()
{
    ReadPara();
    AllocMem();
    
    return 1;
}

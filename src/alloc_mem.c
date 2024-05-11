/* allocate memory */

#include "mdtat.h"

#include <stdlib.h>
#include <string.h>

#define Allocmem(var, num, type)                \
    var = (type *)malloc((num) * sizeof(type))
#define Allocmem2(var, num1, num2, type)        \
    Allocmem(var, num1, type *);                  \
    Allocmem(var[0], (num1) * (num2), type);    \
    for (i = 1; i < num1; ++i)                  \
        var[i] = var[i - 1] + num2;

void AllocMem()
{
    int i;

    /* dump file */
    Allocmem(dr, Natom, VecR);
    Allocmem(box, Nframe, VecR);
    Allocmem2(atom, Nframe, Natom, Atom);

    /* computing properties */
    Allocmem(MSD, Nrepeat, double);
    Allocmem(NGP, Nrepeat, double);
    Allocmem(SISF, Nrepeat, double);
    Allocmem(Xhi4, Nrepeat, double);

    return;
}
#include "mdtat.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zlib.h>

void ReadDump()
{
    Read_Ntotal;
    Read_PBC;
    for (i = 0; i < Ntotal; ++i)
        Read(id, x, y, z);

    return;
}


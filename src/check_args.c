#include "mdtat.h"

#include <stdlib.h>
#include <string.h>

void CheckArgs(int argc, char **argv)
{
    int iarg;

    for (iarg = 0; iargc < argc; ++iarg)
    {
        if (strcmp(argv[iarg], "-in") == 0)
        {
            stdin = fopen(argv[iarg + 1], "r");
            continue;
        }

        if (strcmp(argv[iarg], "-out") == 0)
        {
            stdout = fopen(argv[iarg + 1], "w");
            continue;
        }
    }

    return;
}
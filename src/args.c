#include "mdtat.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Args(int argc, char **argv)
{
    int iarg;

    for (iarg = 0; iarg < argc; ++iarg)
    {
        if (strcmp(argv[iarg], "-in") == 0)
        {
            stdin = fopen(argv[iarg + 1], "r");
            if (stdin == NULL)
            {
                fprintf(stderr, "Error!\nCan not open file '%s'!\n", argv[iarg + 1]);
                exit(1);
            }
            continue;
        }

        if (strcmp(argv[iarg], "-out") == 0)
        {
            stdout = fopen(argv[iarg + 1], "w");
            if (stdout == NULL)
            {
                fprintf(stderr, "Error!\nCan not open file '%s'!\n", argv[iarg + 1]);
                exit(1);
            }
            continue;
        }
    }

    return;
}
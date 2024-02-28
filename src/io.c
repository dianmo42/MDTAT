/* Input and Output */

#include "mdtat.h"

#include <stdio.h>

FILE *OpenFile(const char *filename, const char *modes)
{
    FILE *ptr = fopen(filename, "r");

    switch (modes[0])
    {
        case 'r':
            if (ptr == NULL)
            {
                fprintf(stderr, "Error: Failed to open file '%s'\n", filename);
                exit(1);
            }
            fclose(ptr);
            break;
        case 'w':
            if (ptr != NULL)
            {
                fprintf(stdout, "Attention: Overwrite existing file '%s'\n", filename);
            }
            fclose(ptr);
            break;
        default:
            fclose(ptr);
            break;
    }

    ptr = fopen(filename, modes);

    return ptr;
}
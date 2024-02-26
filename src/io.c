/* Input and Output */

#include "mdtat.h"

#include <stdio.h>

FILE *OpenFile(const char *filename, const char *modes)
{
    FILE *ptr;
    ptr = fopen(filename, "r");
    switch (modes[0])
    {
        case 'r':
            if (ptr == NULL)
            {
                printf(stderr, "Error: Can not open file '%s'\n", filename);
                exit(1);
            }
            fclose(fp);
            break;
        case 'w':
            if (ptr != NULL)
            {
                printf(stdout, "Attention: Overwriting file '%s'\n", filename);
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
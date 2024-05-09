#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    char buff[256], *token;
    for (int i = 0; i < 3; ++i)
    {
        fgets(buff, 256, stdin);
    }
    rewind(stdin);
    fgets(buff, 256, stdin);
    token = strtok(buff, " ");
    fprintf(stdout, "%s", token);

    return 0;    
}
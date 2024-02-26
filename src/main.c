#include "mdtat.h"
#include "functions.h"

int main(int argc, char **argv)
{
    Initialize();
    
    for (int istep = 0; istep < Nstep; ++istep)
    {
        ReadDump(istep);
        Compute(istep);
    }

    Output();

    return 0;
}
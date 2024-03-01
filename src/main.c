#include "mdtat.h"
#include "functions.h"

int main(int argc, char **argv)
{
    ReadPara();
    AllocMem();
    
    for (int istep = 0; istep < Nstep + 1; ++istep)
    {
        ReadDump(istep);

        /* save refference configuration */
        if (istep % Nfreq == 0)
        {
            SaveConf(istep);
            memcpy(r_ref[istep / Nfreq], r_cur, Dimension * Natom * sizeof(double));
            memcpy(box_ref[istep / Nfreq], box_cur, Dimension * sizeof(double));
        }

        /* compute correlation function  */
        for (int i_ref = 0; i_ref < Ncount; ++i_ref)
        {
            int i_gap = istep - i_ref * Nfreq;
            if (istep - i_ref * Nfreq < 1)
                break;
            
            for (int i_repeat = 0; i_repeat < Nrepeat; ++i_repeat)
            {
                if (i_gap != )
            }
        }
        Compute(istep);
    }

    Output();

    return 0;
}
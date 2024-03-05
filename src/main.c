#include "mdtat.h"
#include "functions.h"

int main(int argc, char **argv)
{
    ReadPara();
    AllocMem();

    int istep, i_ref, i_line;
    fp_in = OpenFile(dumpfile, "r");
    for (istep = 0; istep < Nstep + 1; ++istep)
    {
        /* read dump file               */
        for (i_line = 0; i_line < Natom + 9; ++i_line)
            fgets(buff[i_line], 256, fp_in);
        
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

            if (i_gap < 1)
                break;
            if (i_gap % Nevery)
                break;
            
            Compute(i_ref, i_gap);
        }
    }

    Output();

    return 0;
}
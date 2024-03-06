#include "mdtat.h"
#include "functions.h"

#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    ReadPara();
    AllocMem();

    int istep, i_ref, i_gap, i_line;
    FILE *fp_dump = OpenFile(dump_file, "r");
    for (istep = 0; istep < Nstep + 1; ++istep)
    {
        /* read dump file               */
        for (i_line = 0; i_line < Natom + 9; ++i_line)
            fgets(dump_buff[i_line], 256, fp_dump);
        
        /* save refference configuration */
        if (istep % Nfreq == 0)
        {
            i_ref = istep / Nfreq;
            if (i_ref < Ncount)
            {
                SaveConf(istep);
                memcpy(r_ref[i_ref], r_cur, Dimension * Natom * sizeof(double));
                memcpy(box_ref[i_ref], box_cur, Dimension * sizeof(double));
            }
        }

        /* compute correlation function  */
        for (i_ref = 0; i_ref < Ncount; ++i_ref)
        {
            i_gap = istep - i_ref * Nfreq;

            if (i_gap < 1 || i_gap > max_sample)
                continue;
            if (i_gap % Nevery)
                continue;
            
            SaveConf(istep);
            Compute(i_ref, i_gap / Nevery);
        }
    }

    Output();

    return 0;
}
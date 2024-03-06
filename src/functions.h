#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H

FILE *OpenFile(const char *filename, const char *modes);
void ReadPara();
void AllocMem();
void SaveConf(int current_step);
void Compute(int i_ref, int t);
void Compute_MSD(int t);
void Compute_SISF(int t);
void Output();

#endif
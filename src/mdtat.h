/* Molecular Dynamics Trajectory Analyzing Tool (MDTAT)
 * Post-processing of MD trajectories from LAMMPS simulations
 * Auther: dianmo
 * Email: dianmo42@outlook.com
 * */

#ifndef _MDTAT_H
#define _MDTAT_H

/* functions */
void Args(int argc, char **argv);
void Input();
void AllocMem();
void ReadDump();
void Compute(int t0, int t);
void Output();

/* structure */
typedef struct
{
    double x, y, z;
} VecR;

typedef struct
{
    int type;
    double x, y, z;
    double vx, vy, vz;
} Atom;

/* variables */
extern int Natom, Nframe;
extern double timestep;
extern VecR *dr;
extern VecR *box;
extern Atom **atom;

extern int Nfreq, Nevery, Nrepeat;
extern double *MSD, *NGP;
extern double *SISF, *Xhi4, qmax;

#endif
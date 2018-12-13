#ifndef SYSTEM
#define SYSTEM

#include <iostream>             /* cout, etc */
#include <gsl/gsl_rng.h>        /* GSL stuff */
#include <math.h>               /* Math */
#include <string.h>             /* Strings */

using namespace std;


/* Classes and Structures */
struct position {
        int x, y;
        int dir;
};

struct sysVar {
        int N;			/* Number of simulation runs */
        int L;			/* System length */
        int D;			/* Detection radius */
        int bc;                 /*
	 			 * Boundary Condition Type
				 * 0 - No boundaries
				 * 1 - Periodic boundaries
                                 * 2 - Absorbing boundaries /wo lateral move
                                 * 3 - Absorbing boundaries /w lateral move
				 */
        int ch;                 /*
                                 * Chemotaxis functionality
                                 * 0 - p constant
                                 * 1 - p linear decreasing - full range
				 * 2 - p linear increasing - full range
				 * 3 - p parabolic up - full range
				 * 4 - p parabolic down - full range
				 * 5 - p lin dec with limited range
				 * 6 - p para down with limited range
				 * 7 - Power law down
				 * -1 - testing case
                                 */
        double alpha;            /* Release probability in abs bound */
        position tarPos;
};


/* Variables */
extern sysVar svar;
extern gsl_rng *gen;


/* Functions */
void ReadCommandLine(int argc, char const *argv[],
	 		double &p,
			int &N,
			int &L,
                        int &D,
                        double &alpha,
                        int &ch,
                        double &p_min,
                        double &p_max);
void setupEnv();
void initTarget();

#endif

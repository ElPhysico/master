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
                        double &alpha);
void setupEnv();
void initTarget();

#endif

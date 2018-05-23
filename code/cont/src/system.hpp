#ifndef SYSTEM
#define SYSTEM

#include <iostream>		/* cout, etc */
//#include <fstream>		/* fstream */
#include <gsl/gsl_rng.h>	/* GSL stuff */
#include <math.h>		/* Math */
#include <string.h>		/* Strings */

using namespace std;


/* Classes and Structures */
struct position {
	double x, y /* z, */;
	double phi;
};

struct sysVar {
	int N;			/* Number of simulation runs */
	double L;		/* System length */
	double D;		/* Detection radius */
	int bc;			/*
	 			 * Boundary Condition Type
				 * 0 - No boundaries
				 * 1 - Periodic boundaries
                                 * 2 - Absorbing boundaries /wo lateral move
                                 * 3 - Absorbing boundaries /w lateral move
				 */
	position tarPos;	/* Target Position */
};


/* Variables */
extern sysVar svar;
extern gsl_rng *gen;


/* Functions */
void ReadCommandLine(int argc, char const *argv[],
	 		double &p,
			int &N,
			double &L,
			double &D);
void setupEnv();
void initTarget();

#endif

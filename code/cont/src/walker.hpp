#ifndef WALKER
#define WALKER

#include "system.hpp"		/* System Variables etc */
#include <cmath>		/* Complex math */
#include <complex>		/* Complex numbers */
#include "Faddeeva.hpp"		/* Math functions for complex numbers */
#include "rtnorm.hpp"		/* Truncated Gaussian Random Numbers */
#include <limits>		/* Infinity */

using namespace std;


/* Classes and Structures */
class Walker {
	int angDis; 		/* Angle distribution type */
	double p, sigma;	/* Persistency, Standard Deviation */

	/* Function descriptions see system.cpp */
	double avCos(double tmp);
	void setSigma(double tmp);
	double truncGauDis(double a, double b, double mu);
	void detAngDis();
	double ranAng();
	bool outOfBound();
	void correctPos();
	bool traCheck();
	double traSqdistToTarget();
public:
	double stepL;	/* Steplength */
	position pos;	/* Coordinates + origin angle of walker */
	position oldpos;

	void setup(double newp);
	void init();
	void step();
	bool targetFound();
	//double sqdistToTarget();

	void pr_pos(ostream &out = cout);
	//void msd(sysVar svar, int nSteps = 1e3);

	/* Functions to check correctness of program */
	void turningAngleDistribution(string &file, double p);
	double actualP(double p);
};


/* Variables */
extern Walker walker;


/* Functions */


#endif

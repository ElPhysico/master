#ifndef FPT
#define FPT

#include "system.hpp"
#include "walker.hpp"
#include "functions.hpp"
//#include <utility>
//#include <fstream>		/* fstream */

/* Functions */
pair<double, double> chmfpt();
void MFPT(string &file, double p);
void chMFPT(string &file);
void linearMFPT(string &file, double p_min, double p_max);
void parabolicMFPT(string &file, double p_min, double p_max);
void gaussianMFPT(string &file, double mu, double sigma);

#endif

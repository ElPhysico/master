#ifndef FPT
#define FPT

#include "system.hpp"
#include "walker.hpp"
#include <utility>
#include <fstream>		/* fstream */

/* Functions */
pair<double, double> fpt(double pf);
bool fileExists(string &file);
void headerFPT(string &file);
void printFPT(string &file, double p, pair<double, double> data, double scale);
double findDiffFPT(string &file);

#endif

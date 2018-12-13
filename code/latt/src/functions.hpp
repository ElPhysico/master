#ifndef FUNCTIONS
#define FUNCTIONS

#include "system.hpp"
#include "walker.hpp"

/* Functions */
double dist(position w, position t);
bool fileExists(string &file);
void wallFreq(string &file, long int sampleSteps, double p);
void startingPosDistribution(string &file, int samples);

#endif

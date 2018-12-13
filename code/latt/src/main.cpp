#include "system.hpp"
#include "walker.hpp"
#include "fpt.hpp"
#include "functions.hpp"
#include <sstream>

using namespace std;


/* Variables */
int N = 1e4;			/* Number of simulation runs */
int L = 200;			/* System length */
int D = 1;			/* Detection radius */
int bc = 1;			/*
			 	 * Boundary Condition Type
			 	 * 0 - No boundaries
			 	 * 1 - Periodic boundaries
			 	 * 2 - Absorbing boundaries /wo lateral move
			 	 * 3 - Absorbing boundaries /w lateral move
			 	 */
int ch = 0;			/*
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
double p = 0.9;			/* Persistency parameter */
double alpha = 0.1;		/* Release probability from abs. wall */
int stepL = 1;			/* Step length of searcher */


/* Functions */
template <typename T>
string toString (T Number)
{
	stringstream ss;
	ss << Number;
	return ss.str();
}

void setupSysVar();


int main(int argc, char const *argv[])
{
        cout << ":: Setting up...";

	double p_min = 0.0, p_max = 1.0;

        ReadCommandLine(argc, argv, p, N, L, D, alpha, ch, p_min, p_max);
        setupEnv();
        setupSysVar();
	walker.setup(p);
        cout << "\n-> successful!";

        walker.stepL = stepL;

	// /* Testing Area */
	// string file = "./data/TESTING/startDis.dat";
	// startingPosDistribution(file, svar.N);
	// chMFPT(file);
	pair<double, double> tmp = chmfpt();
	cout << "\nMFPT over " << svar.N << " runs: " << tmp.first;
	// /*Testing Area */

        /* Main part of program here, calculations etc... */
        // string file = "./data/TESTING/";
	// string file = "/localdisk/kklein/masterthesis/latt/data/ch/";
	// file += "gaussianMfpt.dat";
	// gaussianMFPT(file, p_min, p_max);
	// linearMFPT(file, p_min, p_max);
	// parabolicMFPT(file, p_min, p_max);
	// file += "chMFPT-ch=";
	// file += toString(svar.ch);
	// file += ".dat";

        cout << "\n\n:: Finishing program...";

        cout << "\n-> Executing done!";
        cout << "\n";
        return 0;
}


/* Functions */
void setupSysVar()
{
        svar.N = N;
        svar.bc = bc;
	svar.ch = ch;
        svar.L = L;
        svar.D = D;
	svar.alpha = alpha;

        cout << "\n System Variables:";
	cout << "\n ==> Boundary Type: " << svar.bc;
	if (svar.bc == 2 || svar.bc == 3)
		cout << "\tAlpha = " << svar.alpha;
	cout << "\n ==> System Length: " << svar.L;
	cout << "\n ==> Detection Radius: " << svar.D;
	cout << "\n ==> Ensembles: " << svar.N;
}

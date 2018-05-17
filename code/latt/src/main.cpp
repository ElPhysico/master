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
int bc = 2;			/*
			 	 * Boundary Condition Type
			 	 * 0 - No boundaries
			 	 * 1 - Periodic boundaries
			 	 * 2 - Absorbing boundaries /wo lateral move
			 	 * 3 - Absorbing boundaries /w lateral move
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
        ReadCommandLine(argc, argv, p, N, L, D, alpha);
        setupEnv();
        setupSysVar();
        cout << "\n-> successful!";

        walker.stepL = stepL;

	// /* Testing Area */
	// string file = "./data/TESTING/wallhits.dat";
	// wallFreq(file, 1e6, p);
	// /*Testing Area */

        /* Main part of program here, calculations etc... */
        string file = "./data/TESTING/mfpt.dat";
	MFPT(file, p);

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

#include "system.hpp"
#include "walker.hpp"
//#include "img.hpp"
#include "fpt.hpp"
#include "functions.hpp"
#include <sstream>

using namespace std;


/* Variables */
int N = 1e4;			/* Number of simulation runs */
double L = 200.0;		/* System length */
double D = 1.0;			/* Detection radius */
int bc = 1;			/*
			 	 * Boundary Condition Type
			 	 * 0 - No boundaries
			 	 * 1 - Periodic boundaries
			 	 * 2 - Absorbing boundaries /wo lateral move
			 	 * 3 - Absorbing boundaries /w lateral move
			 	 */
double p = 0.9;			/* Persistency parameter */
double stepL = 1.0;		/* Step length of searcher */

/*bool graOut = false;	/*
 			 * Set true for output of trajectory in
			 * ./png/trajectories/. In this version of the program
			 * only one trajectory for the values above will be
			 * given as an example. If you want more and different
			 * trajectories you need to alter the code accordingly.
			 */


/* Functions */
/* C++ before 11 doesnt support the .to_string() of the string lib -> durga */
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
	ReadCommandLine(argc, argv, p, N, L, D);
	setupEnv();
	setupSysVar();
	cout << "\n-> successful!";

	walker.stepL = stepL;

	// /* This serves as example of the graphical output functions */
	// /* This is not functional anymore but can be used with few effort */
	// cout << "\nGraphical output: ";
	// if (graOut) {
	// 	cout << "yes";
	// 	walker.setup(p);
	// 	initTarget();
	// 	walker.init();
	// 	string imgfile = "./png/trajectories/p=";
	// 	imgfile += toString(p).substr(0, 4);
	// 	initPNG(imgfile);	/* Initialize png img */
	// 	while (!walker.targetFound()) {
	// 		walker.step();
	// 		updatePNG();	/* Update png img with new position */
	// 	}
	// 	drawPNG();	/* Draw img to file and destroy img */
	// } else {
	// 	cout << "no";
	// }
	// /* END graphics example */


	/* Main Program Part */
	/*
	 * For simulation on durga change path to
	 * "/localdisk/kklein/Masterarbeit/data/....."
	 */
	// string file = "./data/prep/mfpt-N=";
	string file = "/localdisk/kklein/masterthesis/cont/data/deter/";
	file += "MFPT-D=";
	file += toString(svar.D);
	file += ".dat";
	MFPT(file, p);
	//walker.turningAngleDistribution(file, p);

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

	cout << "\n System Variables:";
	cout << "\n ==> Boundary Type: " << svar.bc;
	cout << "\n ==> System Length: " << svar.L;
	cout << "\n ==> Detection Radius: " << svar.D;
	cout << "\n ==> Ensembles: " << svar.N;
}

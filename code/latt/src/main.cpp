#include "system.hpp"
#include "walker.hpp"
#include "fpt.hpp"
#include <sstream>

using namespace std;


/* Variables */
int nRuns = 1e4;
int sysL = 200;
int bc = 2;
double p = 0.9;
double alpha = 0.1;
int stepL = 1;
int detecR = stepL;


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
        ReadCommandLine(argc, argv, p, nRuns, sysL, detecR, alpha);
        setupEnv();
        setupSysVar();
        cout << "\n-> successful!";

        walker.stepL = stepL;

	/* Testing Area */
	walker.absorbCounter = 0;
	walker.wallFreq = 0;
	long int sampleSteps = 1e9;
	walker.setup(p);
	initTarget();
	walker.init();
	for (long int steps = 0; steps < sampleSteps; steps++) {
		walker.step();
	}
	cout << "\n\n#Steps = " << sampleSteps;
	cout << "\nWalker was absorbed " << walker.absorbCounter << " times.";
	cout << " That is around " << walker.absorbCounter / (1.0 * svar.nRuns);
	cout << " times on the average run.";
	cout << "\nWalker hit the wall " << walker.wallFreq << " times.";
	cout << " That is around " << walker.wallFreq / (1.0 * svar.nRuns);
	cout << " times on the average run.";

	string file = "/localdisk/kklein/Masterarbeit/lattice/wallFreq/";
	file += "WF-alpha=" + toString(svar.alpha) + ".dat";
	FILE *outf;
	if (!fileExists(file)) {
		outf = fopen(file.c_str(), "a");
		fprintf(outf, "#System variables:");
		fprintf(outf, "\n#Boundary type: %i", svar.bc);
		if (svar.bc == 2 || svar.bc == 3)
			fprintf(outf, "\tAlpha = %f", svar.alpha);
		fprintf(outf, "\n#System Length: %i", svar.sysL);
		fprintf(outf, "\n#Detection Radius: %i", svar.detecR);
		fprintf(outf, "\n#Fixed steps: %i", sampleSteps);
		fprintf(outf, "\n\n#p\tWall-Frequency\trel.-WF");
		fclose(outf);
	}
	outf = fopen(file.c_str(), "a");
	fprintf(outf, "\n%3f\t%i", p, walker.wallFreq);
	fprintf(outf, "\t%f", (1.0 * walker.wallFreq) / sampleSteps);
	fclose(outf);
	/*Testing Area */

        // /* Main part of program here, calculations etc... */
        // // string file = "./data/alpha/";
        // string file = "/localdisk/kklein/Masterarbeit/lattice/alpha/tarCen/L=20/";
        // // // file += "fpt-D=" + toString(svar.detecR) + ".dat";
	// file += "fpt-alpha=" + toString(svar.alpha) + ".dat";
        // headerFPT(file);
        // cout << "\n\n:: Starting simulation for MFPT...";
        // pair<double, double> fpt_p = fpt(p);
        // double fpt_scale = findDiffFPT(file);
        // if (p == 0.25)
        //         fpt_scale = fpt_p.first;
        // printFPT(file, p, fpt_p, fpt_scale);

        cout << "\n\n:: Finishing program...";

        cout << "\n-> Executing done!";
        cout << "\n";
        return 0;
}


/* Functions */
void setupSysVar()
{
        svar.nRuns = nRuns;
        svar.bc = bc;
        svar.sysL = sysL;
        svar.detecR = detecR;
	svar.alpha = alpha;

        cout << "\nSystem Variables:";
	cout << "\n==> Boundary Type: " << svar.bc;
	if (svar.bc == 2 || svar.bc == 3)
		cout << "\tAlpha = " << svar.alpha;
	cout << "\n==> System Length: " << svar.sysL;
	cout << "\n==> Detection Radius: " << svar.detecR;
	cout << "\n==> Ensembles: " << svar.nRuns;
}

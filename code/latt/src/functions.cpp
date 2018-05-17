#include "functions.hpp"

/* Functions */
bool fileExists(string &file)
{
        if (FILE *f = fopen(file.c_str(), "r"))
                return true;
        else
                return false;
}

/* Calculates #wallhits in samplesteps steps and writes data into file. */
void wallFreq(string &file, long int sampleSteps, double p)
{
        walker.absorbCounter = 0;
        walker.wallHits = 0;
        walker.setup(p);
        initTarget();
        walker.init();

        for (long int steps = 0; steps < sampleSteps; steps++) {
                walker.step();
        }

        cout << "\n\nIn " << sampleSteps << " steps the walker hit the wall ";
        cout << walker.wallHits << " times and was absorbed ";
        cout << walker.absorbCounter << " times.";
        cout << "\nThis relates to " << walker.wallHits / (1.0 * sampleSteps);
        cout << " wall-hits per step.";

        FILE *outf;
        if (!fileExists(file)) {
                outf = fopen(file.c_str(), "a");
                fprintf(outf, "#System variables:");
		fprintf(outf, "\n#Boundary type: %i", svar.bc);
		if (svar.bc == 2 || svar.bc == 3)
			fprintf(outf, "\tAlpha = %f", svar.alpha);
		fprintf(outf, "\n#System Length: %i", svar.L);
		fprintf(outf, "\n#Detection Radius: %i", svar.D);
		fprintf(outf, "\n#Fixed steps: %i", sampleSteps);
		fprintf(outf, "\n\n#p\tWall-Frequency\trel.-WF");
		fclose(outf);
        }
        outf = fopen(file.c_str(), "a");
        fprintf(outf, "\n%3f\t%i", p, walker.wallHits);
	fprintf(outf, "\t%f", (1.0 * walker.wallHits) / sampleSteps);
	fclose(outf);
}

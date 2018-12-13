#include "functions.hpp"

/* Functions */
double dist(position w, position t)
{
        return sqrt((w.x - t.x) * (w.x - t.x) + (w.y - t.y) * (w.y - t.y));
}

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

/* Samples starting position distribution. */
position genRanPos() {
        position tmp;
        tmp.x = gsl_rng_uniform_int(gen, svar.L);
        tmp.y = gsl_rng_uniform_int(gen, svar.L);

        if (dist(tmp, svar.tarPos) < svar.D)
                tmp = genRanPos();

        return tmp;
}
void startingPosDistribution(string &file, int samples)
{
        int intervals = 100;
        int *counter;
        counter = new int[intervals];
        double d = (svar.L / sqrt(2)) / (1.0 * intervals);
        position tmpos;

        initTarget();

        for (int i = 0; i < samples; i++) {
                /* Generating of position */
                tmpos = genRanPos();
                int j = 0;
                do {
                        if (dist(tmpos, svar.tarPos) < (j + 1) * d)
                                counter[j]++;
                        j++;
                } while (dist(tmpos, svar.tarPos) >= j * d);
        }

        FILE *outf;
        outf = fopen(file.c_str(), "a");
        fprintf(outf, "#Number of sampled starting positions: %i", samples);
        fprintf(outf, "\n\n#Distance\tRelative weight");
        double sum = 0.0, tmp;
        for (int i = 0; i <= intervals; i++) {
                tmp = (1.0 * counter[i] / (1.0 * samples));
                sum += tmp;
                fprintf(outf, "\n%.3f\t%f", i * d, tmp);
        }
        fclose(outf);
        delete[] counter;
        cout << "\nSum = " << sum;
}

#include "fpt.hpp"


/* Functions */
pair<double, double> mfpt(double pf)
{
        cout << "\n ==> p = " << pf << "...";
        cout << "\n";
        double totalSteps = 0.0;
        double totalSqSteps = 0.0;
        for (int run = 0; run < svar.N; run++) {
                double nSteps = 0.0;
                walker.setup(pf);
                initTarget();
                walker.init();
                while (!walker.targetFound()) {
                        nSteps += 1.0;
                        walker.step();
                }
                totalSteps += nSteps;
                totalSqSteps += nSteps * nSteps;
        }
        double fpt = totalSteps / (1.0 * svar.N);
        double fpt2 = totalSqSteps / (1.0 * svar.N);

        double stDev = sqrt(fpt2 - fpt * fpt);
        cout << "-> finished!";
        return make_pair(fpt, stDev / sqrt(svar.N));
}

void headerMFPT(string &file)
{
        if (!fileExists(file)) {
                FILE *outf;
                outf = fopen(file.c_str(), "a");
                fprintf(outf, "#System variables:");
		fprintf(outf, "\n#Boundary type: %i", svar.bc);
                if (svar.bc == 2 || svar.bc == 3)
        		fprintf(outf, "\tAlpha = %f", svar.alpha);
		fprintf(outf, "\n#System Length: %i", svar.L);
		fprintf(outf, "\n#Detection Radius: %i", svar.D);
		fprintf(outf, "\n#Ensembles: %i", svar.N);
		fprintf(outf, "\n\n#p\t<fpt>\tdelta\t<fpt>/<fpt>_0\tdelta\n");
		fclose(outf);
        }
}

void printMFPT(string &file, double p, pair<double, double> data)
{
        FILE *outf;
        outf = fopen(file.c_str(), "a");
        fprintf(outf, "%.3f", p);
        fprintf(outf, "\t%f\t%f", data.first, data.second);
	fprintf(outf, "\t0.0\t0.0");
	fprintf(outf, "\n");
	fclose(outf);
}

void MFPT(string &file, double p)
{
        headerMFPT(file);
        cout << "\n\n:: Starting MFPT simulation...";
        pair<double, double> tmp = mfpt(p);
        printMFPT(file, p, tmp);
}

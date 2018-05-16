#include "fpt.hpp"


/* Functions */
pair<double, double> fpt(double pf)
{
        cout << "\n==> p = " << pf << "...";
        cout << "\n";
        double totalSteps = 0.0;
        double totalSqSteps = 0.0;
        for (int run = 0; run < svar.nRuns; run++) {
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
        double fpt = totalSteps / (1.0 * svar.nRuns);
        double fpt2 = totalSqSteps / (1.0 * svar.nRuns);

        double stDev = sqrt(fpt2 - fpt * fpt);
        cout << "-> finished!";
        return make_pair(fpt, stDev / sqrt(svar.nRuns));
}

bool fileExists(string &file)
{
        if (FILE *f = fopen(file.c_str(), "r"))
                return true;
        else
                return false;
}

void headerFPT(string &file)
{
        if (!fileExists(file)) {
                FILE *outf;
                outf = fopen(file.c_str(), "a");
                fprintf(outf, "#System variables:");
		fprintf(outf, "\n#Boundary type: %i", svar.bc);
                if (svar.bc == 2 || svar.bc == 3)
        		fprintf(outf, "\tAlpha = %f", svar.alpha);
		fprintf(outf, "\n#System Length: %i", svar.sysL);
		fprintf(outf, "\n#Detection Radius: %i", svar.detecR);
		fprintf(outf, "\n#Ensembles: %i", svar.nRuns);
		fprintf(outf, "\n\n#p\t<fpt>\tdelta\t<fpt>/<fpt>_0\tdelta\n");
		fclose(outf);
        }
}

void printFPT(string &file, double p, pair<double, double> data, double scale)
{
        FILE *outf;
        outf = fopen(file.c_str(), "a");
        fprintf(outf, "%.3f", p);
        fprintf(outf, "\t%f\t%f", data.first, data.second);
	fprintf(outf, "\t%f", data.first / scale);
	fprintf(outf, "\t%f", data.second / scale);
	fprintf(outf, "\n");
	fclose(outf);
}

void skip_lines(int k, ifstream &datei) {
    int l = 0;
    string skippedline;
    while (datei && l < k) {
        getline(datei, skippedline);
        l++;
    }
}

double findDiffFPT(string &file)
{
        ifstream infile;
        infile.open(file.c_str());
        if (!infile) {
                cerr << "\nError: can't read file\n";
        } else {
                skip_lines(7, infile);
                double val1, val2, val3, val4, val5;
		while (infile >> val1 >> val2 >> val3 >> val4 >> val5) {
			if (val1 == 0.25)
				return val2;
		}
        }
}

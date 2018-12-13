#include "fpt.hpp"


/* Functions */
/* Returns fpt+error averaged over N using const parameter p for the walker. */
pair<double, double> mfpt(double pf)
{
        cout << "\n ==> p = " << pf << "...";
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
        cout << "\n-> finished!";
        return make_pair(fpt, stDev / sqrt(svar.N));
}

/* Different chemotaxis-functionalities. */
double linDec(double d)
{
        double tmp = 1.0 - d / (svar.L / sqrt(2));
        if (tmp < 0.0)
                tmp = 0.0;
        return tmp;
}
double linDec(double d, double a)
{
        if (a < 0.0)
                a = 0.0;
        if (a > 1.0)
                a = 1.0;
        double tmp = 1.0 - (1.0 - a) * d / (svar.L / sqrt(2));
        if (tmp < (1.0 - a))
                tmp = 1.0 - a;
        return tmp;
}
double linInc(double d)
{
        double tmp = d / (svar.L / sqrt(2));
        if (tmp > 1.0)
                tmp = 1.0;
        return tmp;
}
double parabolicUp(double d)
{
        double c = 2 * sqrt(2);
        c /= svar.L;
        double tmp = c * c * (d - 1 / c) * (d - 1 / c);
        if (tmp > 1.0)
                tmp = 1.0;
        return tmp;
}
double parabolicDown(double d)
{
        double c = 2 * sqrt(2);
        c /= svar.L;
        double tmp = 1.0 - c * c * (d - 1 / c) * (d - 1 / c);
        if (tmp < 0.0)
                tmp = 0.0;
        return tmp;
}
double parabolicDown(double d, double a)
{
        if (a < 0.0)
                a = 0.0;
        if (a > 1.0)
                a = 1.0;
        double c = sqrt(2) / svar.L;
        double tmp = 1.0 - a * c * c * d * d;
        if (tmp < 0.0)
                tmp = 0.0;
        return tmp;
}
double powerDown(double d, double a)
{
        double c = sqrt(2) / svar.L;
        double tmp = 1.0 - pow(c, a) * pow(d, a);
        if (tmp < 0.0)
                tmp = 0.0;
        return tmp;
}

/* Console output for ch functions. */
void consoleCH()
{
        cout << "\n ==> p according to";
        switch (svar.ch) {
        case 0: /* Constant */
                cout << " constant p = " << walker.returnP() << "...";
                break;
        case 1: /* Linear decreasing - full range */
                cout << " linear decreasing function over full range...";
                break;
        case 2: /* Linear increasing - full range */
                cout << " linear increasing function over full range...";
                break;
        case 3: /* Parabolic up - full range */
                cout << " parabolic up function over full range...";
                break;
        case 4: /* Parabolic down - full range */
                cout << " parabolic down function over full range...";
                break;
        case 5: /* Lin dec with limited range */
                cout << " linear decreasing over limited range...";
                break;
        case 6: /* Parabolic down with limited range */
                cout << " parabolic down over limited range...";
                break;
        case 7: /* Power law down */
                cout << " power law down over full range...";
                break;
        case -1: /* Testing case */
                cout << " testing new function...";
                break;
        }
}

/* Returns p according to ch function. */
void setP()
{
        double d, p;
        d = dist(walker.pos, svar.tarPos);
        switch (svar.ch) {
        case 0: /* Constant */
                p = walker.returnP();
                break;
        case 1: /* Linear decreasing - full range */
                p = linDec(d);
                break;
        case 2: /* Linear increasing - full range */
                p = linInc(d);
                break;
        case 3: /* Parabolic up - full range */
                p = parabolicUp(d);
                break;
        case 4: /* Parabolic down - full range */
                p = parabolicDown(d);
                break;
        case 5: /* Lin dec with limited range */
                p = linDec(d, 0.9);
                break;
        case 6: /* Para down limited range */
                p = parabolicDown(d, 0.3);
                break;
        case 7: /* Power down full range */
                p = powerDown(d, 4.0);
                break;
        case -1: /* Testing case */
                double c = sqrt(2) / svar.L;

                // Double Fermi-Dirac
                // p = 1 - 1 / (exp((d - 5.0/*0.5 * 1 / c*/) / 10) + 1);
                // p -= 1 - 1 / (exp((d - 1 / 1.5 / c) / 15.0) + 1);

                // Single Fermi-Dirac
                // p = 0.0 + 1.0 / (exp((d - 1 / 1 / c) / 10) + 1);

                // 1/x
                // p = 10/c / (d + 10/c);

                // parabolic
                // p = - 0.2 * c * c * d * d + 1.0;

                // linear
                p = 1.0 - 0.12 * d * c;


                if (p < 0.0)
                        p = 0.0;
                else if (p > 1.0)
                        p = 1.0;
                // cout << "\nd=" << d << ", p=" << p;
        }
        walker.setup(p);

        // cout << "\n w(" << walker.pos.x << ", " << walker.pos.y << ")";
        // cout << " t(" << svar.tarPos.x << ", " << svar.tarPos.y << ")";
        // cout << " => d = " << d << ", p = " << p;
}

/* Returns fpt+error averaged over N runs using chemotaxis persistency. */
pair<double, double> chmfpt()
{
        consoleCH();

        double totalSteps = 0.0;
        double totalSqSteps = 0.0;
        for (int run = 0; run < svar.N; run++) {
                double nSteps = 0.0;
                initTarget();
                walker.init();
                while (!walker.targetFound()) {
                        setP();
                        nSteps += 1.0;
                        walker.step();
                }
                totalSteps += nSteps;
                totalSqSteps += nSteps * nSteps;
        }
        double fpt = totalSteps / (1.0 * svar.N);
        double fpt2 = totalSqSteps / (1.0 * svar.N);

        double stDev = sqrt(fpt2 - fpt * fpt);
        cout << "\n-> finished!";
        return make_pair(fpt, stDev / sqrt(svar.N));
}

/* Writes header of fpt file. */
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
void headerCHMFPT(string &file)
{
        if (/*!fileExists(file)*/true) {
                FILE *outf;
                outf = fopen(file.c_str(), "a");
                fprintf(outf, "#System variables:");
		fprintf(outf, "\n#Boundary type: %i", svar.bc);
                if (svar.bc == 2 || svar.bc == 3)
        		fprintf(outf, "\tAlpha = %f", svar.alpha);
		fprintf(outf, "\n#System Length: %i", svar.L);
		fprintf(outf, "\n#Detection Radius: %i", svar.D);
		fprintf(outf, "\n#Ensembles: %i", svar.N);
                fprintf(outf, "\n#p(d) = ");
                switch (svar.ch) {
                case 0: /* Constant */
                        fprintf(outf, "%f", walker.returnP());
                        break;
                case 1: /* Linear decreasing - full range */
                        fprintf(outf, "1 - d * sqrt2/L");
                        break;
                case 2: /* Linear increasing - full range */
                        fprintf(outf, "d * sqrt2/L");
                        break;
                case 3: /* Parabolic up - full range */
                        fprintf(outf, "(2sqrt2/L)^2 * (d-L/(2sqrt2))^2");
                        break;
                case 4: /* Parabolic down - full range */
                        fprintf(outf, "1 - (2sqrt2/L)^2 * (d-L/(2sqrt2))^2");
                        break;
                case 5: /* Linear decreasing over limited range */
                        fprintf(outf, "1 - a * d * sqrt2/L");
                        break;
                case 6: /* Para down limited range */
                        fprintf(outf, "1 - a * d^2 * (sqrt2/L)^2");
                        break;
                case 7: /* Power down full range */
                        fprintf(outf, "1 - d^a * (sqrt2/L)^a");
                        break;
                case -1: /* Testing case */
                        break;
                }
                fprintf(outf, "\n\n<fpt>\tdelta");
		fclose(outf);
        }
}

/* Prints the fpt data to the file in file. */
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

void printCHMFPT(string &file, pair<double, double> data)
{
        FILE *outf;
        outf = fopen(file.c_str(), "a");
        fprintf(outf, "\n%f\t%f", data.first, data.second);
        fprintf(outf, "\n#-----------------------------------\n\n\n\n");
	fclose(outf);
}

/* Starts mfpt simulation */
void MFPT(string &file, double p)
{
        headerMFPT(file);
        cout << "\n\n:: Starting MFPT simulation...";
        pair<double, double> tmp = mfpt(p);
        printMFPT(file, p, tmp);
}

void chMFPT(string &file)
{
        headerCHMFPT(file);
        cout << "\n\n:: Starting MFPT simulation...";
        pair<double, double> tmp = chmfpt();
        printCHMFPT(file, tmp);
}

/* Linear search approach functions */
pair<double, double> linearmfpt(double p_min, double p_max)
{
        cout << "\n ==> linear profile with p_min = " << p_min;
        cout << " and p_max = " << p_max;

        double totalSteps = 0.0;
        double totalSqSteps = 0.0;
        double d, p;
        for (int run = 0; run < svar.N; run++) {
                double nSteps = 0.0;
                initTarget();
                walker.init();
                while (!walker.targetFound()) {
                        d = dist(walker.pos, svar.tarPos);
                        p = p_max - (p_max - p_min) * d * sqrt(2) / svar.L;
                        if (p < 0.0)
                                p = 0.0;
                        if (p > 1.0)
                                p = 1.0;
                        walker.setup(p);
                        nSteps += 1.0;
                        walker.step();
                }
                totalSteps += nSteps;
                totalSqSteps += nSteps * nSteps;
        }
        double fpt = totalSteps / (1.0 * svar.N);
        double fpt2 = totalSqSteps / (1.0 * svar.N);

        double stDev = sqrt(fpt2 - fpt * fpt);
        cout << "\n-> finished!";
        return make_pair(fpt, stDev / sqrt(svar.N));
}

void linearHeader(string &file)
{
        if (!fileExists(file)) {
                FILE *outf;
                outf = fopen(file.c_str(), "a");
                fprintf(outf, "#Linear search strategy:");
                fprintf(outf, "\n#p(d) = p_max - (p_max - p_min) * d * sqrt2 / L");
                fprintf(outf, "\n#System variables:");
		fprintf(outf, "\n#Boundary type: %i", svar.bc);
                if (svar.bc == 2 || svar.bc == 3)
        		fprintf(outf, "\tAlpha = %f", svar.alpha);
		fprintf(outf, "\n#System Length: %i", svar.L);
		fprintf(outf, "\n#Detection Radius: %i", svar.D);
		fprintf(outf, "\n#Ensembles: %i", svar.N);
		fprintf(outf, "\n\n#p_min\tp_max\t<fpt>\t<delta>");
		fclose(outf);
        }
}

void printLinearMFPT(string &file,
                  pair<double, double> data,
                  double p_min,
                  double p_max)
{
        FILE *outf;
        outf = fopen(file.c_str(), "a");
        fprintf(outf, "\n%.3f\t%.3f", p_min, p_max);
        fprintf(outf, "\t%f\t%f", data.first, data.second);
	fclose(outf);
}

void linearMFPT(string &file, double p_min, double p_max)
{
        linearHeader(file);
        cout << "\n\n:: Starting MFPT simulation...";
        pair<double, double> tmp = linearmfpt(p_min, p_max);
        printLinearMFPT(file, tmp, p_min, p_max);
}

/* Parabolic search approach functions. */
pair<double, double> parabolicmfpt(double p_min, double p_max)
{
        cout << "\n ==> symmetric parabolic profile with p_min = " << p_min;
        cout << " and p_max = " << p_max;

        double totalSteps = 0.0;
        double totalSqSteps = 0.0;
        double d, p;
        for (int run = 0; run < svar.N; run++) {
                double nSteps = 0.0;
                initTarget();
                walker.init();
                while (!walker.targetFound()) {
                        d = dist(walker.pos, svar.tarPos);
                        p = (d - svar.L / (2 * sqrt(2)));
                        p *= (2 * sqrt(2) / svar.L);
                        p *= -(p_max - p_min) * p;
                        p += p_max;
                        // cout << "\nd=" << d << ", p=" << p;
                        if (p < 0.0)
                                p = 0.0;
                        if (p > 1.0)
                                p = 1.0;
                        walker.setup(p);
                        nSteps += 1.0;
                        walker.step();
                }
                totalSteps += nSteps;
                totalSqSteps += nSteps * nSteps;
        }
        double fpt = totalSteps / (1.0 * svar.N);
        double fpt2 = totalSqSteps / (1.0 * svar.N);

        double stDev = sqrt(fpt2 - fpt * fpt);
        cout << "\n-> finished!";
        return make_pair(fpt, stDev / sqrt(svar.N));
}

void parabolicHeader(string &file)
{
        if (!fileExists(file)) {
                FILE *outf;
                outf = fopen(file.c_str(), "a");
                fprintf(outf, "#Parabolic search strategy:");
                fprintf(outf, "\n#p(d) = p_max - (p_max - p_min)");
                fprintf(outf, " * (d - 200 / 2sqrt2)^2");
                fprintf(outf, " * (2sqrt2 / 200)^2");
                fprintf(outf, "\n#System variables:");
		fprintf(outf, "\n#Boundary type: %i", svar.bc);
                if (svar.bc == 2 || svar.bc == 3)
        		fprintf(outf, "\tAlpha = %f", svar.alpha);
		fprintf(outf, "\n#System Length: %i", svar.L);
		fprintf(outf, "\n#Detection Radius: %i", svar.D);
		fprintf(outf, "\n#Ensembles: %i", svar.N);
		fprintf(outf, "\n\n#p_min\tp_max\t<fpt>\t<delta>");
		fclose(outf);
        }
}

void printParabolicMFPT(string &file,
                  pair<double, double> data,
                  double p_min,
                  double p_max)
{
        FILE *outf;
        outf = fopen(file.c_str(), "a");
        fprintf(outf, "\n%.3f\t%.3f", p_min, p_max);
        fprintf(outf, "\t%f\t%f", data.first, data.second);
	fclose(outf);
}

void parabolicMFPT(string &file, double p_min, double p_max)
{
        parabolicHeader(file);
        cout << "\n\n:: Starting MFPT simulation...";
        pair<double, double> tmp = parabolicmfpt(p_min, p_max);
        printParabolicMFPT(file, tmp, p_min, p_max);
}

/* Gaussian search approach functions. */
pair<double, double> gaussianmfpt(double mu, double sigma)
{
        cout << "\n ==> gaussian profile with mu = " << mu;
        cout << " and sigma = " << sigma;

        double totalSteps = 0.0;
        double totalSqSteps = 0.0;
        double d, p;
        for (int run = 0; run < svar.N; run++) {
                double nSteps = 0.0;
                initTarget();
                walker.init();
                while (!walker.targetFound()) {
                        d = dist(walker.pos, svar.tarPos);
                        p = exp(-(d - mu) * (d - mu) / (2 * sigma * sigma));
                        // cout << "\nd=" << d << ", p=" << p;
                        if (p < 0.0)
                                p = 0.0;
                        if (p > 1.0)
                                p = 1.0;
                        walker.setup(p);
                        nSteps += 1.0;
                        walker.step();
                }
                totalSteps += nSteps;
                totalSqSteps += nSteps * nSteps;
        }
        double fpt = totalSteps / (1.0 * svar.N);
        double fpt2 = totalSqSteps / (1.0 * svar.N);

        double stDev = sqrt(fpt2 - fpt * fpt);
        cout << "\n-> finished! <FPT> = " << fpt;
        return make_pair(fpt, stDev / sqrt(svar.N));
}

void gaussianHeader(string &file)
{
        if (!fileExists(file)) {
                FILE *outf;
                outf = fopen(file.c_str(), "a");
                fprintf(outf, "#Gaussian search strategy:");
                fprintf(outf, "\n#p(d) = exp(-(d - mu)^2 / (2 * sigma^2))");
                fprintf(outf, "\n#System variables:");
		fprintf(outf, "\n#Boundary type: %i", svar.bc);
                if (svar.bc == 2 || svar.bc == 3)
        		fprintf(outf, "\tAlpha = %f", svar.alpha);
		fprintf(outf, "\n#System Length: %i", svar.L);
		fprintf(outf, "\n#Detection Radius: %i", svar.D);
		fprintf(outf, "\n#Ensembles: %i", svar.N);
		fprintf(outf, "\n\n#mu\tsigma\t<fpt>\t<delta>");
		fclose(outf);
        }
}

void printGaussianMFPT(string &file,
                  pair<double, double> data,
                  double mu,
                  double sigma)
{
        FILE *outf;
        outf = fopen(file.c_str(), "a");
        fprintf(outf, "\n%.3f\t%.3f", mu, sigma);
        fprintf(outf, "\t%f\t%f", data.first, data.second);
	fclose(outf);
}

void gaussianMFPT(string &file, double mu, double sigma)
{
        gaussianHeader(file);
        cout << "\n\n:: Starting MFPT simulation...";
        pair<double, double> tmp = gaussianmfpt(mu, sigma);
        printGaussianMFPT(file, tmp, mu, sigma);
}

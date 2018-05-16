#include "system.hpp"


/* Variables */
sysVar svar;
int seed = time(0);
gsl_rng *gen;


/* Functions */
void setupGSL()
{
        gsl_rng_env_setup();
        const gsl_rng_type *type = gsl_rng_default;
        gen = gsl_rng_alloc(type);
        gsl_rng_set(gen, seed);
}

void ReadCommandLine(int argc, char const *argv[],
	 		double &p,
			int &nRuns,
			int &sysL,
                        int &detecR,
                        double &alpha)
{
	for (int i = 1; i < argc; i++) {
		if (strstr(argv[i], "-p="))
			p = atof(argv[i] + 3);
		if (strstr(argv[i], "-nRuns="))
			nRuns = atoi(argv[i] + 7);
		if (strstr(argv[i], "-sysL="))
			sysL = atoi(argv[i] + 6);
                if (strstr(argv[i], "-detecR="))
                        detecR = atoi(argv[i] + 8);
                if (strstr(argv[i], "-alpha="))
                        alpha = atof(argv[i] + 7);
	}
}

void setupEnv()
{
        cout.unsetf(ios::floatfield);
        cout.precision(10);
        setupGSL();
}

void initTarget()
{
        switch (svar.bc) {
        case 0: /* No boundaries */
                break;
        case 1: /* Periodic boundaries */
                svar.tarPos.x = svar.sysL / 2;
                svar.tarPos.y = svar.sysL / 2;
                break;
        case 2: /* Absorbing boundaries /wo lateral move */
                // svar.tarPos.x = gsl_rng_uniform_int(gen, svar.sysL);
                // svar.tarPos.y = gsl_rng_uniform_int(gen, svar.sysL);
                // if (svar.tarPos.x == svar.sysL - 1 || svar.tarPos.x == 0)
                //         initTarget();
                // else if (svar.tarPos.y == svar.sysL - 1 || svar.tarPos.y == 0)
                //         initTarget();
                svar.tarPos.x = svar.sysL / 2;
                svar.tarPos.y = svar.sysL / 2;
                break;
        case 3: /* Absorbing boundaries /w lateral move */
                break;
        }

        // cout << "\n\n:: Setting up target...";
        // cout << "\n-> successful, target position: ";
        // cout << "(" << svar.tarPos.x << ", " << svar.tarPos.y << ")";
}

#include "system.hpp"


/* Variables */
sysVar svar;
int seed = time(0);
// int seed = chrono::system_clock::now().time_since_epoch().count();
//int seed = 1337;
gsl_rng *gen;


/* Functions */
/* Setting up random number generator gen. */
void setupGSL()
{
	gsl_rng_env_setup();
	const gsl_rng_type *type = gsl_rng_default;
	gen = gsl_rng_alloc(type);
	gsl_rng_set(gen, seed);
}

/* Reads command line parameters. */
void ReadCommandLine(int argc, char const *argv[],
	 		double &p,
			int &N,
			double &L,
			double &D)
{
	for (int i = 1; i < argc; i++) {
		if (strstr(argv[i], "-p="))
			p = atof(argv[i] + 3);
		if (strstr(argv[i], "-N="))
			N = atoi(argv[i] + 3);
		if (strstr(argv[i], "-L="))
			L = atof(argv[i] + 3);
		if (strstr(argv[i], "-D="))
			D = atof(argv[i] + 3);
	}
}

/* Setup of environment, different settings and parameters. */
void setupEnv()
{
	cout.unsetf(ios::floatfield);
	cout.precision(10);
	setupGSL();
}

/* Initializes position of target. */
void initTarget()
{
	switch (svar.bc) {
	case 0:	/* No boundaries */
		svar.tarPos.x = gsl_rng_uniform(gen) * svar.L - 0.5 * svar.L;
		svar.tarPos.y = gsl_rng_uniform(gen) * svar.L - 0.5 * svar.L;
		// svar.pos.z = gsl_rng_uniform(gen) * svar.sysL - 0.5 * svar.sysL;
		break;
	case 1: /* Periodic boundaries */
		svar.tarPos.x = 0.0;
		svar.tarPos.y = 0.0;
		break;
	case 2: /* Absorbing boundaries /wo lateral move */
		break;
	case 3: /* Absorbing boundaries /w lateral move */
		break;
	}
}

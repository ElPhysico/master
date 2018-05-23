#include "walker.hpp"


/* Variables */
Walker walker;


/* Functions */
/*
 * Calculates the average of cosine over the [-pi, pi] truncated gaussian
 * distribution with zero mean and tmp standard deviation.
 */
double Walker::avCos(double tmp)
{
	if (tmp == 0.0) {
		return 1.0;
	} else {
		complex<double> i;
		complex<double> z;
		double d;

		d = sqrt(2) * tmp;

		i = -1;
		i = sqrt(i);
		z = Faddeeva::erf((M_PI - i * tmp * tmp) / d);
		z += Faddeeva::erf((M_PI + i * tmp * tmp) / d);
		z /= 2 * Faddeeva::erf(M_PI / d);
		z *= exp(-tmp * tmp / 2.0);

		return z.real();
	}
}

/*
 * Sets sigma to value for which the avCos is equal to the persistency
 * parameter p.
 */
void Walker::setSigma(double tmp)
{
	double xerr = 1e-4;
	double a = 0.0, b = 25.0, mid;	/* 25 corresponds to p = 0.00159926 */
	double p_a, p_mid, p_b;
	do {
		mid = (a+b) / 2.0;

		p_mid = avCos(mid);
		p_a = avCos(a);
		p_b = avCos(b);

		if (fabs(p_mid - tmp) <= xerr) {
			sigma = mid;
			return;
		}
		if (fabs(p_a - tmp) <= xerr) {
			sigma = a;
			return;
		}
		if (fabs(p_b - tmp) <= xerr) {
			sigma = b;
			return;
		}

		if (p_mid > tmp)
			a = mid;
		else if (p_mid < tmp)
			b = mid;
	} while (fabs(p_mid - tmp) >= xerr);

	sigma = mid;
}

/*
 * Returns random variable distributed according to the truncated gaussian
 * distribution with boundaries a < b, mu mean and sigma standard deviation.
 */
double Walker:: truncGauDis(double a, double b, double mu)
{
	pair<double, double> s = rtnorm(gen, a, b, mu, sigma);
 	return s.first;
}

/*
 * Determines which distribution to use in order to calculate turning angles.
 * Sets angDis to 0 in case of persistency parameter p = 0 for uniform
 * distribution.
 * Sets angDis to 1 in case of positive persistency parameter 0 < p <= 1 for
 * truncated gaussian distribution.
 * Sets angDis to -1 in case of negative persistency parameter -1 <= p < 0 for
 * "adjusted" truncated gaussian distribution.
 * Sets angDis to 10 if something went wrong (this should never happen).
 */
void Walker::detAngDis()
{
	if (p == 0.0)
		angDis = 0;
	else if (p < 0.0 && p >= -1.0)
		angDis = -1;
	else if (p > 0.0 && p <= 1.0)
		angDis = 1;
	else
		angDis = 10;
}

/* Sets up walker with new persistency and according parameters. */
void Walker::setup(double newp)
{
	if (newp < -1.0) {
		cout << "Warning: ";
		cout << "p needs to be in [-1.0, 1.0]! p set to p = -1.0.\n";
		p = -1.0;
	} else if (newp > 1.0) {
		cout << "Warning: ";
		cout << "p needs to be in [-1.0, 1.0]! p set to p = 1.0.\n";
		p = 1.0;
	} else {
		p = newp;
	}
	detAngDis();
	switch (angDis) {
	case 0:
		sigma = numeric_limits<double>::infinity();
		break;
	case -1:
		setSigma(-p);
		break;
	case 1:
		setSigma(p);
		break;
	default:
		cout << "Something went wrong!" << endl;
		break;
	}
}

/* Returns random angle according to active distribution. */
double Walker::ranAng()
{
	double tmp;
	bool deterministic = true;
	switch (angDis) {
	case 0:
		tmp = gsl_rng_uniform(gen);
		tmp *= 2.0 * M_PI;
		tmp -= M_PI;
		break;
	case -1:
		tmp = truncGauDis(-M_PI, M_PI, 0.0);
		if (tmp > 0.0)
			tmp -= M_PI;
		else if (tmp <= 0.0)
			tmp += M_PI;
		break;
	case 1:
		if (deterministic) {
			tmp = acos(p);
			if (gsl_rng_uniform(gen) < 0.5)
				tmp *= -1.0;
		} else {
			tmp = truncGauDis(-M_PI, M_PI, 0.0);
		}
		break;
	default:
		cout << "Not good!" << endl;
		break;
	}

	return tmp;
}

/* Initializes walker at starting position and direction. */
void Walker::init()
{
	pos.x = gsl_rng_uniform(gen) * svar.L - 0.5 * svar.L;
	pos.y = gsl_rng_uniform(gen) * svar.L - 0.5 * svar.L;
	// pos.z = gsl_rng_uniform(gen) * svar.sysL - 0.5 * svar.sysL;
	pos.phi = gsl_rng_uniform(gen) * 2.0 * M_PI - M_PI;
	oldpos = pos;

	/* Check if walker is already in detection range */
	double range = svar.D * svar.D;
	if(traSqdistToTarget() < range)
		init();
}

/* Returns true if walker stepped out of boundaries in last step. */
bool Walker::outOfBound()
{
	if (pos.x < -0.5 * svar.L || pos.x >= 0.5 * svar.L)
		return true;
	else if (pos.y < -0.5 * svar.L || pos.y >= 0.5 * svar.L)
		return true;
	else
		return false;
}

/* Corrects the position of the walker depending on the boundary conditions. */
void Walker::correctPos()
{
	switch (svar.bc) {
	case 0:	/* No boundaries */
		break;
	case 1:	/* Periodic boundaries */
		if (pos.x < -0.5 * svar.L)
			pos.x += svar.L;
		else if (pos.x >= 0.5 * svar.L)
			pos.x -= svar.L;
		if (pos.y < -0.5 * svar.L)
			pos.y += svar.L;
		else if (pos.y >= 0.5 * svar.L)
			pos.y -= svar.L;
		break;
	case 2: /* Absorbing boundaries /wo lateral move */
	        break;
	case 3: /* Absorbing boundaries /w lateral move */
		break;
	}
}

/* Lets walker take a step. */
void Walker::step()
{
	oldpos = pos;
	pos.phi += ranAng();
	pos.x += cos(pos.phi) * stepL;
	pos.y += sin(pos.phi) * stepL;
	// pos.z += 0.0;

	if (outOfBound())
		correctPos();
}

/* Returns true if pos or oldpos lie within 2 * D distance to target. */
bool Walker::traCheck()
{
	bool tmp = false;
	double range = svar.D * svar.D;
	double dx, dy;
	dx = pos.x - svar.tarPos.x;
	dy = pos.y - svar.tarPos.y;
	dx *= dx;
	dy *= dy;
	if (dx + dy < 4 * range)
		tmp = true;
	dx = oldpos.x - svar.tarPos.x;
	dy = oldpos.y - svar.tarPos.y;
	dx *= dx;
	dy *= dy;
	if (dx + dy < 4 * range)
		tmp = true;
	return tmp;
}

/* Returns scalar product if positions are interpreted as vectors. */
double dot(position p1, position p2)
{
	return p1.x * p2.x + p1.y * p2.y;
}

/* Returns squared distance if positions are interpreted as vectors. */
double sqdist(position p1, position p2)
{
	return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}

/* Returns smallest distance of line between oldpos and pos and target. */
double Walker::traSqdistToTarget()
{
	//cout << "checking if trajectory crossed detection area...\n";
	/* Here it might be prettier to implement +,- for positions. */
	position op, ot, proj;
	op.x = pos.x - oldpos.x;
	op.y = pos.y - oldpos.y;
	if (op.x == 0.0 && op.y == 0.0)
		return sqdist(oldpos, svar.tarPos);
	ot.x = svar.tarPos.x - oldpos.x;
	ot.y = svar.tarPos.y - oldpos.y;

	double t = dot(ot, op) / dot(op, op);
	proj.x = oldpos.x + t * op.x;
	proj.y = oldpos.y + t * op.y;

	if (t < 0.0)
		return sqdist(oldpos, svar.tarPos);
	else if (t > 1.0)
		return sqdist(pos, svar.tarPos);
	else
	 	return sqdist(proj, svar.tarPos);
}

/* Returns true if walker has crossed the detection radius of target. */
bool Walker::targetFound()
{
	double range = svar.D * svar.D;
	if (traCheck() && traSqdistToTarget() < range)
		return true;
	else
		return false;
}

/* Prints walker position. */
void Walker::pr_pos(ostream &out/*=cout*/)
{
	out << pos.x << "\t" << pos.y << "\n";
}

/* Not used anymore. This was used to check whether the program works. */
// double distSq(double x1, double x2, double y1, double y2)
// {
// 	return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
// }
// void Walker::msd(sysVar svar, int nSteps)
// {
// 	int numRuns = 2 * 1e3;
// 	double *msd;
// 	int *counter;
// 	msd = new double[nSteps + 1];
// 	counter = new int[nSteps + 1];
// 	for (int i = 0; i <= nSteps; i++) {
// 		msd[i] = 0.0;
// 		counter[i] = 0;
// 	}
// 	counter[0] = 1;
//
// 	for (int runs = 0; runs < numRuns; runs++) {
// 		pos.x = 0.0;
// 		pos.y = 0.0;
// 		pos.phi = 0.0;
// 		double *x;
// 		double *y;
// 		x = new double[nSteps + 1];
// 		y = new double[nSteps + 1];
// 		x[0] = pos.x;
// 		y[0] = pos.y;
// 		for (int st = 0; st <= nSteps; st++) {
// 			step(svar);
// 			x[st] = pos.x;
// 			y[st] = pos.y;
// 		}
// 		for (int i = 0; i < nSteps; i++)
// 			for (int j = 1; j <= nSteps - i; j++) {
// 				msd[j] += distSq(x[i + j], x[i], y[i + j], y[i]);
// 				counter[j]++;
// 			}
// 		delete[] x;
// 		delete[] y;
// 	}
//
// 	fstream outf;
// 	string file = "./data/msd_p=" + to_string(p).substr(0, 5);
// 	file += ".dat";
// 	outf.open(file, ios::out);
// 	outf << "#n" << "\t" << "<r^2>" << endl;
// 	for (int i = 0; i <= nSteps; i++)
// 		msd[i] /= (1.0 * counter[i]);
// 	double msd_1 = msd[1];	/* For scaling */
// 	for (int i = 0; i <= nSteps; i++) {
// 		msd[i] /= msd_1;
// 		outf << i << "\t" << msd[i] << endl;
// 	}
//
// 	delete[] msd;
// 	delete[] counter;
// 	outf.close();
// }



/* Correctness functions - use with caution */
/* Writes histogram of turning angle distribution in file. */
void Walker::turningAngleDistribution(string &file, double p)
{
	int samples = 1e7;
	int intervals = 50;
	int *counter;
	counter = new int[intervals];
	double d = 2 * M_PI / (intervals * 1.0);
	double tmp;

	setup(p);
	for (int i = 0; i < samples; i++) {
		tmp = ranAng();
		int j = 0;
		do {
			if (tmp < -M_PI + (j+1) * d)
				counter[j]++;
			j++;
		} while (tmp >= -M_PI + j * d);
	}

	FILE *outf;
	outf = fopen(file.c_str(), "a");
	fprintf(outf, "#Persistency p = %f", p);
	fprintf(outf, "\n#Number of sampled random angles: %i", samples);
	fprintf(outf, "\n#Angle\tRelative weight");
	double sum = 0.0;
	for (int i = 0; i < intervals; i++) {
		tmp = (1.0 * counter[i]) / (1.0 * samples);
		sum += tmp;
		fprintf(outf, "\n%.3f\t%f", -M_PI + i * d, tmp);
	}
	fprintf(outf, "\n%.3f\t%f", M_PI, 0.0);
	fclose(outf);
	delete[] counter;
	cout << "\nSum: " << sum;
}

/* Returns the value of p = <cos x> for randomized x. */
double Walker::actualP(double p)
{
	setup(p);
	int n = 1e4;
	double sum = 0.0;
	for (int i = 0; i < n; i++)
		sum += cos(ranAng());
	return sum / (1.0 * n);
}

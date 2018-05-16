#include "walker.hpp"


/* Variables */
Walker walker;


/* Functions */
void Walker::setup(double newpf)
{
        if (newpf < 0.0) {
		cout << "Warning: ";
		cout << "p needs to be in [0, 1.0]! p set to p = 0.\n";
		pf = 0.0;
	} else if (newpf > 1.0) {
		cout << "Warning: ";
		cout << "p needs to be in [0, 1.0]! p set to p = 1.0.\n";
		pf = 1.0;
	} else {
		pf = newpf;
	}

        pb = (1.0 - pf) / 3;
        po = 1.0 - pf - pb;
}

void Walker::init()
{
        pos.x = gsl_rng_uniform_int(gen, svar.sysL);
        pos.y = gsl_rng_uniform_int(gen, svar.sysL);
        pos.dir = gsl_rng_uniform_int(gen, 4) + 1;

        oldpos = pos;

        if (targetFound())
                init();
        if (svar.bc == 2) {
                if (pos.x == 0) {
                        if (pos.y == 0 || pos.y == svar.sysL - 1)
                                init();
                } else if (pos.x == svar.sysL - 1) {
                        if (pos.y == 0 || pos.y == svar.sysL - 1)
                                init();
                }
        }
}

int Walker::getDirection()
{
        double ran = gsl_rng_uniform(gen);
        // cout << "\n#var ran: " << ran;

        double tower[4];
        tower[0] = 0.0;
        tower[1] = pf;
        tower[2] = pf + pb;
        tower[3] = pf + pb + po;

        int tmp = 0;
        for (int i = 0; i < 3; i++) {
                if (ran >= tower[i])
                        tmp = i;
        }

        /* tmp -> 0: straight, 1: backwards, 2: orthogonal */
        int direction;
        switch (tmp) {
        case 0:
                direction = oldpos.dir;
                break;
        case 1:
                direction = (oldpos.dir + 2) % 4;
                if (direction == 0)
                        direction = 4;
                break;
        case 2:
                int turn = 1;
                if (gsl_rng_uniform(gen) < 0.5)
                        turn = -1;
                direction = (oldpos.dir + turn) % 4;
                if (direction == 0)
                        direction = 4;
                break;
        }

        return direction;
}

bool Walker::outOfBound()
{
        if (pos.x < 0 || pos.x >= svar.sysL)
                return true;
        else if (pos.y < 0 || pos.y >= svar.sysL)
                return true;
        else
                return false;
}

void Walker::correctPos()
{
        switch (svar.bc) {
        case 0: /* No boundaries */
                break;
        case 1: /* Periodic boundaries */
                if (pos.x < 0)
                        pos.x += svar.sysL;
                else if (pos.x >= svar.sysL)
                        pos.x -= svar.sysL;
                if (pos.y < 0)
                        pos.y += svar.sysL;
                else if (pos.y >= svar.sysL)
                        pos.y -= svar.sysL;
                break;
        case 2: /* Absorbing boundaries /wo lateral move */
                break;
        case 3: /* Absorbing boundaries /w lateral move */
                break;
        }
}

void Walker::innerStep()
{
        // cout << "\ninnerStep begin";
        pos.dir = getDirection();
        switch (pos.dir) {
        case 1: /* step to the right */
                pos.x += stepL;
                break;
        case 2: /* step to the top */
                pos.y += stepL;
                break;
        case 3: /* step to the left */
                pos.x -= stepL;
                break;
        case 4: /* step to the bottom */
                pos.y -= stepL;
                break;
        }
}

void Walker::step()
{
        oldpos = pos;
        switch (svar.bc) {
        case 0: /* No boundaries */
                break;
        case 1: /* Periodic boundaries */
                innerStep();
                if (outOfBound())
                        correctPos();
                break;
        case 2: /* Absorbing boundaries /wo lateral move */
                bool tmp = gsl_rng_uniform(gen) <= svar.alpha;
                if (pos.x == 0) {
                        if (tmp) {
                                pos.x += stepL;
                                pos.dir = 1;
                                wallFreq++;
                        } else {
                                absorbCounter++;
                        }
                } else if (pos.x == svar.sysL - 1) {
                        if (tmp) {
                                pos.x -= stepL;
                                pos.dir = 3;
                                wallFreq++;
                        } else {
                                absorbCounter++;
                        }
                } else if (pos.y == 0) {
                        if (tmp) {
                                pos.y += stepL;
                                pos.dir = 2;
                                wallFreq++;
                        } else {
                                absorbCounter++;
                        }
                } else if (pos.y == svar.sysL - 1) {
                        if (tmp) {
                                pos.y -= stepL;
                                pos.dir = 4;
                                wallFreq++;
                        } else {
                                absorbCounter++;
                        }
                } else {
                        innerStep();
                }
                break;
        }
}

bool Walker::targetFound()
{
        int dx, dy;
        dx = fabs(pos.x - svar.tarPos.x);
        dy = fabs(pos.y - svar.tarPos.y);

        if (dx + dy <= svar.detecR)
                return true;
        else
                return false;
}

void Walker::coutVars()
{
        cout << "\n\n:: Walker Variables:";
        cout << "\n==> pf = " << pf << ", pb = " << pb << ", po = " << po;
        cout << "\n==> Old-Position: (" << oldpos.x << ", " << oldpos.y << ")";
        cout << "\n==> Old-Direction: " << oldpos.dir;
        cout << "\n==> Position: (" << pos.x << ", " << pos.y << ")";
        cout << "\n==> Direction: " << pos.dir;
}
#ifndef WALKER
#define WALKER

#include "system.hpp"

/* Classes and Structures */
class Walker {
        double pf;       /* Forward probability */
        double pb;      /* Backward probability */
        double po;      /* Orthogonal probability */

        int getDirection();
        bool outOfBound();
        void correctPos();
        void innerStep();
public:
        int stepL;
        position pos;
        position oldpos;
        int absorbCounter, wallHits;

        void setup(double newp);
        double returnP();
        void init();
        // int getDirection();
        void step();
        bool targetFound();

        void coutVars();
};


/* Variables */
extern Walker walker;

#endif

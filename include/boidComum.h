#ifndef BOID_COMUM_H
#define BOID_COMUM_H

#include "boid.h"

class BoidComum : public Boid{
    public:
        BoidComum(Vector3 _pos);
        void draw();
};


#endif /* BOID_COMUM */
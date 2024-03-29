#ifndef BOID_COMUM_H
#define BOID_COMUM_H

#include "boid.h"

class BoidComum : public Boid{
    public:
        BoidComum(Vector3 _pos);
        void draw();

        void addVelocity(Vector3 deltaV);
        void fugir(Vector3 newV);
    private:
        Quaternion totalRotation;
};


#endif /* BOID_COMUM */
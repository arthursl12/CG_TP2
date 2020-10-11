#ifndef BOID_H
#define BOID_H

#include <Quaternion.hpp>
#include "gObject.h"

class Boid : public GameObject{
    friend class Bando;
    public:
        Boid(Vector3 _pos);
        void draw() = 0;
        void update();

        void addVelocity(Vector3 deltaV);
        bool operator!=(Boid& outro);
    protected:
        Vector3 velocity;
        Vector3 frente;
        Vector3 cima;
        Vector3 esq;

        int flapTimer;
};

#endif
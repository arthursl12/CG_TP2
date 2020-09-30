#ifndef BOID_H
#define BOID_H

#include "gObject.h"

class Boid : public GameObject{
    friend class Bando;
    public:
        Boid(Vector3 _pos);
        void draw() = 0;
        void update();
    

};

class BoidComum : public Boid{
    public:
        BoidComum(Vector3 _pos);
        void draw();
};

class BoidLider : public Boid{
    public:
        BoidLider(Vector3 _pos);
        void draw();
};

#endif
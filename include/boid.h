#ifndef BOID_H
#define BOID_H

#include "gObject.h"

class Boid : public GameObject{
    public:
        Boid(vec3 _pos);
        void draw() = 0;
        void update();
    

};

class BoidComum : public Boid{
    public:
        BoidComum(vec3 _pos);
        void draw();
};

class BoidLider : public Boid{
    public:
        BoidLider(vec3 _pos);
        void draw();
};

#endif
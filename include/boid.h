#ifndef BOID_H
#define BOID_H

#include "gObject.h"

class Boid : public GameObject{
    public:
        Boid(vec3 _pos);
        void draw();
        void update();
    

};

#endif
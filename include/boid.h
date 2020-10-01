#ifndef BOID_H
#define BOID_H

#include "gObject.h"
#include "Quaternion.hpp"

class Boid : public GameObject{
    friend class Bando;
    public:
        Boid(Vector3 _pos);
        void draw() = 0;
        void update();

        void addVelocity(Vector3& deltaV);
    protected:
        Vector3 velocity;
        Vector3 frente;


        Vector3 oldV;
        Quaternion pose;
        Quaternion oldPose;
    

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
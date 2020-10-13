#ifndef BOID_LIDER_H
#define BOID_LIDER_H

#include "boid.h"

class BoidLider : public Boid{
    friend class Bando;
    public:
        BoidLider(Vector3 _pos);
        void draw();
        void update() override;

        void yawEsq();
        void yawDir();
        void pitchUp();
        void pitchDown();
    private:
        Quaternion totalRotation;

        void atualizaEixos(Quaternion q);
};

#endif /* BOID_LIDER */
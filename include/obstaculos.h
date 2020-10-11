#ifndef OBSTACULO_H
#define OBSTACULO_H

#include "gObject.h"
#include "Quaternion.hpp"

class Obstaculo : public GameObject{
    friend class Bando;
    public:
        Obstaculo(Vector3 _pos){pos = _pos;};
        void draw() = 0;
        void update();
};

class Esfera : public Obstaculo{
    public:
        Esfera(Vector3 _pos) : Obstaculo(_pos){};
        void draw();
};
#endif
#ifndef OBSTACULO_H
#define OBSTACULO_H

#include <Quaternion.hpp>
#include "gObject.h"


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
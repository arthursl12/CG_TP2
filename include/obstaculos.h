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
        virtual bool proximo(Vector3 ponto) = 0;
        virtual Vector3 maisProximo(Vector3 ponto) = 0;
};

class Esfera : public Obstaculo{
    public:
        Esfera(Vector3 _pos);
        void draw();
        Vector3 maisProximo(Vector3 ponto);
        bool proximo(Vector3 ponto);
    private:
        double raio;
};
#endif
#ifndef PIRAMIDE_H
#define PIRAMIDE_H

#include "gObject.h"
#include "quadrado.h"

class Piramide : public GameObject{
    public:
        Piramide(vec3 _pos, vec3 vertice, Quadrado quad);
        void draw();
        void update();
    private:
        vec3 vertice;
        Quadrado quad;

};

#endif
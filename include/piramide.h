#ifndef PIRAMIDE_H
#define PIRAMIDE_H

#include "gObject.h"
#include "quadrado.h"

class Piramide : public GameObject{
    public:
        Piramide(vec3 _pos, vec3 _vert, GLfloat _ax, GLfloat _ay, GLfloat _az, GLfloat _lado);
        void draw();
        void update();
        void drawVector(vec3 vec, vec3 origem);
    private:
        vec3 vertice;
        Quadrado quad;

};

#endif
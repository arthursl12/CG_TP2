#ifndef QUADRADO_H
#define QUADRADO_H

#include "gObject.h"
#include "linalg.h"

class Quadrado : public GameObject{
    friend class Piramide;
    public:
        Quadrado(vec3 _pos, GLfloat _ax, GLfloat _ay, GLfloat _az, GLfloat _lado);
        void draw();
        void update();
    private:
        GLfloat lado;
        GLfloat ax;
        GLfloat ay;
        GLfloat az;
};

#endif
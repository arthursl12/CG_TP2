#ifndef QUADRADO_H
#define QUADRADO_H

#include "gObject.h"
#include "linalg.h"

class Quadrado : public GameObject{
    public:
        Quadrado(vec3 _pos, GLfloat ax, GLfloat ay, GLfloat az, GLfloat _lado);
        void draw();
        void update();
    private:
        GLfloat lado;
        GLfloat ax;
        GLfloat ay;
        GLfloat az;
};

#endif
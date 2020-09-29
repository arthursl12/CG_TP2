#ifndef RETANGULO_H
#define RETANGULO_H

#include "gObject.h"
#include "linalg.h"

class Retangulo : public GameObject{
    friend class Piramide;
    public:
        Retangulo(vec3 _pos, GLfloat _ax, GLfloat _ay, GLfloat _az, GLfloat _lado1, GLfloat _lado2);
        void draw();
        void update();
    private:
        GLfloat lado1;
        GLfloat lado2;
        GLfloat ax;
        GLfloat ay;
        GLfloat az;
};

#endif
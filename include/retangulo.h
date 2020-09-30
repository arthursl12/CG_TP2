/**
 * Classe Retângulo.
 *
 * Gere um ente geométrico retângulo
 *
 * @param 
 *      _pos  : coordenada do centro do retângulo
 *      _ax   : rotação em torno do eixo x
 *      _ay   : rotação em torno do eixo y
 *      _az   : rotação em torno do eixo z
 *      _lado1: lado1 do retângulo
 *      _lado2: lado2 do retângulo
 */
#ifndef RETANGULO_H
#define RETANGULO_H


#include "Vector3.hpp"
#include "gObject.h"
#include "linalg.h"

class Retangulo : public GameObject{
    friend class Piramide;
    public:
        Retangulo(Vector3 _pos, GLfloat _ax, GLfloat _ay, GLfloat _az, GLfloat _lado1, GLfloat _lado2);
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
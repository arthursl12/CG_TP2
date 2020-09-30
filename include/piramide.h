/**
 * Classe Pirâmide.
 *
 * Gere um ente geométrico de uma pirâmide de base retangular
 *
 * @param 
 *      _pos  : coordenada do centro da base
 *      _vert : coordenada do vértice da pirâmide, a partir do centro da base
 *      _ax   : rotação da base em torno do eixo x
 *      _ay   : rotação da base em torno do eixo y
 *      _az   : rotação da base em torno do eixo z
 *      _lado1: lado1 do retângulo da base
 *      _lado2: lado2 do retângulo da base
 */
#ifndef PIRAMIDE_H
#define PIRAMIDE_H

#include "gObject.h"
#include "Vector3.hpp"
#include "retangulo.h"

class Piramide : public GameObject{
    public:
        Piramide(Vector3 _pos, Vector3 _vert, GLfloat _ax, GLfloat _ay, GLfloat _az, GLfloat _lado, GLfloat _lado2);
        void draw();
        void update();
        void drawVector(Vector3 vec, Vector3 origem);
    private:
        Vector3 vertice;
        Retangulo quad;
};

#endif
/**
 * Classe Pirâmide.
 *
 * Gere um ente geométrico de uma pirâmide de base quadrilátera
 *
 * @param 
 *      _pos  : coordenada do centro da base
 *      _vert : coordenada do vértice da pirâmide, a partir do centro da base
 *      _ax   : rotação da base em torno do eixo x
 *      _ay   : rotação da base em torno do eixo y
 *      _az   : rotação da base em torno do eixo z
 *      _lado : lado do quadrilátero da base
 *  
 */
#ifndef PIRAMIDE_H
#define PIRAMIDE_H

#include "gObject.h"
#include "retangulo.h"

class Piramide : public GameObject{
    public:
        Piramide(vec3 _pos, vec3 _vert, GLfloat _ax, GLfloat _ay, GLfloat _az, GLfloat _lado, GLfloat _lado2);
        void draw();
        void update();
        void drawVector(vec3 vec, vec3 origem);
    private:
        vec3 vertice;
        Retangulo quad;

};

#endif
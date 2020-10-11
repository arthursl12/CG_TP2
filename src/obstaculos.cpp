#include <GL/glu.h>
#include "obstaculos.h"

Esfera::Esfera(Vector3 _pos):
    Obstaculo(_pos)
{
    raio = 35;
}

void Esfera::draw(){
    glPushMatrix();
    glTranslatef(pos.X, pos.Y, pos.Z);
    GLUquadricObj *quadratic;
    quadratic = gluNewQuadric();
    gluSphere(quadratic, raio, 30,30);

    glPopMatrix();
}

bool Esfera::proximo(Vector3 ponto){
    Vector3 distVec = pos - ponto;
    double dist = Vector3::Magnitude(distVec);

    if (dist <= raio * 2.5){
        return true;
    }else{
        return false;
    }
}

void Obstaculo::update(){

}
#include <GL/glu.h>
#include "obstaculos.h"

void Esfera::draw(){
    glPushMatrix();
    glTranslatef(pos.X, pos.Y, pos.Z);
    GLUquadricObj *quadratic;
    quadratic = gluNewQuadric();
    gluSphere(quadratic,35,30,30);

    glPopMatrix();
}

void Obstaculo::update(){

}
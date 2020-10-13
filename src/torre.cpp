#include <GL/glu.h>
#include <Vector3.hpp>
#include <Quaternion.hpp>
#include <Matrix3x3.hpp>
#include "utils.h"
#include "torre.h"

Torre::Torre(Vector3 _pos, double _height, double _radius):   
    Obstaculo(_pos)
{
    cylH = _height;
    conH = _height/1.5;
    totalHeight = _height + _height/1.5;
    radius = _radius;
    conRad = radius*1.5;
}

/**
 * @return True, se o objeto está próximo do obstáculo;
 * False, do contrário
**/
bool Torre::proximo(Vector3 ponto){
    Vector3 distVec = maisProximo(ponto) - ponto;
    double dist = Vector3::Magnitude(distVec);
    if (dist <= radius * 2){
        return true;
    }else{
        return false;
    }
}

Vector3 Torre::maisProximo(Vector3 ponto){
    if (ponto.Y >= pos.Y + totalHeight){
        return pos + Vector3(0,totalHeight,0);
    }else{
        return pos + Vector3(0,ponto.Y,0);
    }
}


void Torre::draw(){
    // Corpo da Torre
    glPushMatrix();
    Quaternion qx = Quaternion::FromAngleAxis(-M_PI/2,Vector3(1,0,0));
    Matrix3x3 m1 = Matrix3x3::FromQuaternion(qx);
    glMultMatrixd(expande(m1));

    glColor3f(1,1,102/255);
    GLUquadricObj *quadratic;
    quadratic = gluNewQuadric();
    gluCylinder(quadratic,
                radius,     // Raio da base
                radius,     // Raio do topo
                cylH,     // Altura
                32,         // Slices
                32);        // Stacks
    glPopMatrix();

    // "Chapéu" da Torre
    glPushMatrix();
    qx = Quaternion::FromAngleAxis(-M_PI/2,Vector3(1,0,0));
    m1 = Matrix3x3::FromQuaternion(qx);
    glMultMatrixd(expande(m1));
    glTranslatef(0,0,cylH);

    glColor3f(0.8,0.1,0.3);
    quadratic = gluNewQuadric();
    gluCylinder(quadratic,
                conRad,     // Raio da base
                0,     // Raio do topo
                conH,     // Altura
                64,         // Slices
                32);        // Stacks
    glPopMatrix();
}

void Torre::update(){
}
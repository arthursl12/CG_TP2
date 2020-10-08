#include <GL/glu.h>
#include <Vector3.hpp>
#include <Quaternion.hpp>
#include <Matrix3x3.hpp>
#include "utils.h"
#include "torre.h"

Torre::Torre(Vector3 _pos, double _height, double _radius){
    pos = _pos;
    height = _height;
    radius = _radius;
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
                height,     // Altura
                32,         // Slices
                32);        // Stacks
    glPopMatrix();

    // "Chapéu" da Torre
    glPushMatrix();
    qx = Quaternion::FromAngleAxis(-M_PI/2,Vector3(1,0,0));
    m1 = Matrix3x3::FromQuaternion(qx);
    glMultMatrixd(expande(m1));
    glTranslatef(0,0,height);

    glColor3f(0.8,0.1,0.3);
    quadratic = gluNewQuadric();
    gluCylinder(quadratic,
                radius*1.5,     // Raio da base
                0,     // Raio do topo
                height/1.5,     // Altura
                32,         // Slices
                32);        // Stacks
    glPopMatrix();


}

void Torre::update(){
}
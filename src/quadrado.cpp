#include "quadrado.h"

Quadrado::Quadrado(vec3 _pos, GLfloat _ax, GLfloat _ay, GLfloat _az, GLfloat _lado){
    pos = _pos;
    ax = _ax;
    ay = _ay;
    az = _az;
    lado = _lado;
}

void Quadrado::draw(){
    glPushMatrix();
    glColor3f(0,1,0);
    glTranslatef( pos.x, pos.y, pos.z);
    glRotatef(ax,1,0,0); 
    glRotatef(ay,0,1,0); 
    glRotatef(az,0,0,1);
    glTranslatef(-pos.x,-pos.y,-pos.z);
    
    glBegin(GL_QUADS); 
        glNormal3f(0,0,1);
        glVertex3f(pos.x-lado/2, pos.y-lado/2, pos.z);
        glVertex3f(pos.x+lado/2, pos.y-lado/2, pos.z);
        glVertex3f(pos.x+lado/2, pos.y+lado/2, pos.z);
        glVertex3f(pos.x-lado/2, pos.y+lado/2, pos.z);
    glEnd();



    glPopMatrix();
}

void Quadrado::update(){ }
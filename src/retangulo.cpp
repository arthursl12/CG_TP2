#include "retangulo.h"

Retangulo::Retangulo(Vector3 _pos, GLfloat _ax, GLfloat _ay, GLfloat _az, GLfloat _lado1, GLfloat _lado2){
    pos = _pos;
    ax = _ax;
    ay = _ay;
    az = _az;
    lado1 = _lado1;
    lado2 = _lado2;
}

void Retangulo::draw(){
    glPushMatrix();
        glTranslatef(pos.X, pos.Y, pos.Z);
        glRotatef(ax,1,0,0); 
        glRotatef(ay,0,1,0); 
        glRotatef(az,0,0,1);
        glTranslatef(-pos.X,-pos.Y,-pos.Z);
        
        glColor3f(0,1,0);
        glBegin(GL_QUADS); 
            glNormal3f(0,0,1);
            glVertex3f(pos.X - lado1/2, pos.Y - lado2/2, pos.Z);
            glVertex3f(pos.X + lado1/2, pos.Y - lado2/2, pos.Z);
            glVertex3f(pos.X + lado1/2, pos.Y + lado2/2, pos.Z);
            glVertex3f(pos.X - lado1/2, pos.Y + lado2/2, pos.Z);
        glEnd();
    glPopMatrix();
}

void Retangulo::update(){ }
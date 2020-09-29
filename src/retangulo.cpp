#include "retangulo.h"

Retangulo::Retangulo(vec3 _pos, GLfloat _ax, GLfloat _ay, GLfloat _az, GLfloat _lado1, GLfloat _lado2){
    pos = _pos;
    ax = _ax;
    ay = _ay;
    az = _az;
    lado1 = _lado1;
    lado2 = _lado2;
}

void Retangulo::draw(){
    glPushMatrix();
        glTranslatef( pos.x, pos.y, pos.z);
        glRotatef(ax,1,0,0); 
        glRotatef(ay,0,1,0); 
        glRotatef(az,0,0,1);
        glTranslatef(-pos.x,-pos.y,-pos.z);
        
        glColor3f(0,1,0);
        glBegin(GL_QUADS); 
            glNormal3f(0,0,1);
            glVertex3f(pos.x - lado1/2, pos.y - lado2/2, pos.z);
            glVertex3f(pos.x + lado1/2, pos.y - lado2/2, pos.z);
            glVertex3f(pos.x + lado1/2, pos.y + lado2/2, pos.z);
            glVertex3f(pos.x - lado1/2, pos.y + lado2/2, pos.z);
        glEnd();
    glPopMatrix();
}

void Retangulo::update(){ }
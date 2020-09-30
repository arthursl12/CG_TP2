#include <vector>
#include <iostream>
#include "piramide.h"
#include "utils.h"

#include "Quaternion.hpp"
#include "Matrix3x3.hpp"

Piramide::Piramide(vec3 _pos, vec3 _vert, GLfloat _ax, GLfloat _ay, GLfloat _az, GLfloat _lado1, GLfloat _lado2):
    quad(_pos, _ax, _ay, _az, _lado1, _lado2)
{
    pos = _pos;
    vertice = _vert;
}

void Piramide::draw(){
    glPushMatrix();
        // "Restaura" a rotação do quadrado
        glTranslatef( pos.x, pos.y, pos.z);
        Quaternion qx = Quaternion::FromAngleAxis(M_PI*quad.ax/180, Vector3(1,0,0));
        Quaternion qy = Quaternion::FromAngleAxis(M_PI*quad.ay/180, Vector3(0,1,0));
        Quaternion qz = Quaternion::FromAngleAxis(M_PI*quad.az/180, Vector3(0,0,1));

        Quaternion q = qx * qy * qz;
        Matrix3x3 m1 = Matrix3x3::FromQuaternion(q);
    
        glMultMatrixd(expande(m1));
        glTranslatef(-pos.x,-pos.y,-pos.z);

        vec3 vertTransl = pos + vertice; 

        GLfloat lado1 = quad.lado1;
        GLfloat lado2 = quad.lado2;
        vec3 vq1(pos.x - lado1/2, pos.y - lado2/2, pos.z);
        vec3 vq2(pos.x + lado1/2, pos.y - lado2/2, pos.z);
        vec3 vq3(pos.x + lado1/2, pos.y + lado2/2, pos.z);
        vec3 vq4(pos.x - lado1/2, pos.y + lado2/2, pos.z);
        std::vector<vec3> vertices{vq1, vq2, vq3, vq4};
        std::vector<vec3> normais;
        std::vector<vec3> arestas;



        for (int i = 0; i < 4; i++){
            glBegin(GL_TRIANGLES);
                vec3 v1 = vertices[i];
                vec3 v2 = vertices[i+1];
                if (i == 3){
                    v1 = vertices[0];
                    v2 = vertices[3];
                }
                
                vec3 aresta = -v1 + v2;
                vec3 normal = aresta * vertTransl;
                normal.normalizar();
                normais.push_back(normal);
                arestas.push_back(aresta);
                
                glNormal3f(normal.x, normal.y, normal.z);
                glVertex3f(vertTransl.x, vertTransl.y, vertTransl.z);
                glVertex3f(v1.x, v1.y, v1.z);
                glVertex3f(v2.x, v2.y, v2.z);
            glEnd();
        }
        
    glPopMatrix();
}

void Piramide::update(){ }

void Piramide::drawVector(vec3 vec, vec3 origem){
    vec3 copy = vec;
    if (copy.norma() >= 100){
        copy.normalizar();
        copy = copy * 5;
    }

    std::cout << copy << std::endl;
    glColor3f(1,0,0);
    glBegin(GL_TRIANGLES); 
        glNormal3f(0.0, 1.0, 0.0); 
        glVertex3f(origem.x, origem.y - 1, origem.z);
        glVertex3f(origem.x + copy.x, origem.y + copy.y, origem.z + copy.z);
        glVertex3f(origem.x, origem.y + 1, origem.z);
    glEnd();
}
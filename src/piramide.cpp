#include <Quaternion.hpp>
#include <Matrix3x3.hpp>
#include <vector>
#include <iostream>
#include "utils.h"
#include "piramide.h"

Piramide::Piramide(Vector3 _pos, Vector3 _vert, GLfloat _ax, GLfloat _ay, GLfloat _az, GLfloat _lado1, GLfloat _lado2):
    quad(_pos, _ax, _ay, _az, _lado1, _lado2)
{
    pos = _pos;
    vertice = _vert;
}

void Piramide::draw(){
    glPushMatrix();
        // "Restaura" a rotação do quadrado
        glTranslatef( pos.X, pos.Y, pos.Z);
        Quaternion qx = Quaternion::FromAngleAxis(M_PI*quad.ax/180, Vector3(1,0,0));
        Quaternion qy = Quaternion::FromAngleAxis(M_PI*quad.ay/180, Vector3(0,1,0));
        Quaternion qz = Quaternion::FromAngleAxis(M_PI*quad.az/180, Vector3(0,0,1));

        Quaternion q = qx * qy * qz;
        Matrix3x3 m1 = Matrix3x3::FromQuaternion(q);
    
        glMultMatrixd(expande(m1));
        glTranslatef(-pos.X,-pos.Y,-pos.Z);

        Vector3 vertTransl = pos + vertice; 

        GLfloat lado1 = quad.lado1;
        GLfloat lado2 = quad.lado2;
        Vector3 vq1(pos.X - lado1/2, pos.Y - lado2/2, pos.Z);
        Vector3 vq2(pos.X + lado1/2, pos.Y - lado2/2, pos.Z);
        Vector3 vq3(pos.X + lado1/2, pos.Y + lado2/2, pos.Z);
        Vector3 vq4(pos.X - lado1/2, pos.Y + lado2/2, pos.Z);
        std::vector<Vector3> vertices{vq1, vq2, vq3, vq4};
        std::vector<Vector3> normais;
        std::vector<Vector3> arestas;



        for (int i = 0; i < 4; i++){
            glBegin(GL_TRIANGLES);
                Vector3 v1 = vertices[i];
                Vector3 v2 = vertices[i+1];
                if (i == 3){
                    v1 = vertices[0];
                    v2 = vertices[3];
                }
                
                Vector3 aresta = -v1 + v2;
                Vector3 vecNaFace = -vertTransl + v1;
                Vector3 normal = Vector3::Cross(vecNaFace, aresta);
                Vector3 unitNormal = Vector3::Normalized(normal);
                normais.push_back(unitNormal);
                arestas.push_back(aresta);
                
                glNormal3f(unitNormal.X, unitNormal.Y, unitNormal.Z);
                glVertex3f(vertTransl.X, vertTransl.Y, vertTransl.Z);
                glVertex3f(v1.X, v1.Y, v1.Z);
                glVertex3f(v2.X, v2.Y, v2.Z);
            glEnd();
        }
        
    glPopMatrix();
}

void Piramide::update(){ }

void Piramide::drawVector(Vector3 vec, Vector3 origem){
    Vector3 copy = vec;
    if (Vector3::Magnitude(copy) >= 100){
        copy = Vector3::Normalized(copy);
        copy = copy * 5;
    }

    std::cout << copy.data << std::endl;
    glColor3f(1,0,0);
    glBegin(GL_TRIANGLES); 
        glNormal3f(0.0, 1.0, 0.0); 
        glVertex3f(origem.X, origem.Y - 1, origem.Z);
        glVertex3f(origem.X + copy.X, origem.Y + copy.Y, origem.Z + copy.Z);
        glVertex3f(origem.X, origem.Y + 1, origem.Z);
    glEnd();
}
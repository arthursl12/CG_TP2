#include <vector>
#include <iostream>
#include "piramide.h"


Piramide::Piramide(vec3 _pos, vec3 _vert, GLfloat _ax, GLfloat _ay, GLfloat _az, GLfloat _lado):
    quad(_pos, _ax, _ay, _az, _lado)
{
    pos = _pos;
    vertice = _vert;
}

void Piramide::draw(){
    glPushMatrix();
        // "Restaura" a rotação do quadrado
        // glTranslatef( pos.x, pos.y, pos.z);
        glRotatef(quad.ax,1,0,0); 
        glRotatef(quad.ay,0,1,0); 
        glRotatef(quad.az,0,0,1);
        glTranslatef(-pos.x,-pos.y,-pos.z);

        GLfloat lado = quad.lado;
        vec3 vq1(pos.x - lado/2, pos.y - lado/2, pos.z);
        vec3 vq2(pos.x + lado/2, pos.y - lado/2, pos.z);
        vec3 vq3(pos.x + lado/2, pos.y + lado/2, pos.z);
        vec3 vq4(pos.x - lado/2, pos.y + lado/2, pos.z);
        std::vector<vec3> vertices{vq1, vq2, vq3, vq4};
        std::vector<vec3> normais;
        std::vector<vec3> arestas;



        for (int i = 0; i < 4; i++){
            glColor3f(1,0,0.5);
            glBegin(GL_TRIANGLES);
                vec3 v1 = vertices[i];
                vec3 v2 = vertices[i+1];
                if (i == 3){
                    v1 = vertices[0];
                    v2 = vertices[3];
                }
                
                vec3 aresta = -v1 + v2;
                vec3 normal = aresta * vertice;
                normal.normalizar();
                normais.push_back(normal);
                arestas.push_back(aresta);
                std::cout << " V1: " << v1 << std::endl;
                std::cout << "-V1: " << -v1 << std::endl;
                std::cout << " V2: " << v2 << std::endl;
                std::cout << "  N: " << normal << std::endl;
                std::cout << "  A: " << aresta << std::endl;
                std::cout << std::endl;
                
                glNormal3f(normal.x, normal.y, normal.z);
                glVertex3f(vertice.x, vertice.y, vertice.z);
                glVertex3f(v1.x, v1.y, v1.z);
                glVertex3f(v2.x, v2.y, v2.z);
            glEnd();
        }
        for (vec3 vec : normais){
            drawVector(vec, vertice);
        }
        for (int i = 0; i < 4; i++){
            drawVector(arestas[i], vertices[i]);
        }
        drawVector(vertice, vec3(0,0,0));
        
        
        // glRotatef(quad.ax,1,0,0); 
        // glRotatef(quad.ay,0,1,0); 
        // glRotatef(quad.az,0,0,1);
        // glTranslatef(-pos.x,-pos.y,-pos.z);
        
        // glColor3f(1,0,0.5f);
        // glBegin(GL_QUADS); 
        //     glNormal3f(0,0,1);
        //     lado = quad.lado;
        //     glVertex3f(pos.x - lado/2, pos.y - lado/2, pos.z);
        //     glVertex3f(pos.x + lado/2, pos.y - lado/2, pos.z);
        //     glVertex3f(pos.x + lado/2, pos.y + lado/2, pos.z);
        //     glVertex3f(pos.x - lado/2, pos.y + lado/2, pos.z);
        // glEnd();
    glPopMatrix();
    // quad.draw();
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
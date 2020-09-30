#include "GL/glut.h"
#include "GL/gl.h"
#include <iostream>

#include "Matrix3x3.hpp"
#include "Quaternion.hpp"


#include "world.h"
#include "bando.h"

World::World(){
    this->reset();
    bando = std::make_shared<Bando>(vec3(15,15,15));
    bando->addBoid();
}

World::World(const World& old){
    this->alvo = old.alvo;
    this->observador = old.observador;
    this->normalObsvd = old.normalObsvd;
    this->bando = old.bando;
}

void World::drawGeradores(){
    glColor3f(1,1,0);
    glBegin(GL_TRIANGLES); 
        // Seta +Y
        glNormal3f(0.0, 1.0, 0.0); 
        glVertex3f(-5,0,0);
        glVertex3f(0,100,0);
        glVertex3f(5,0,0);
    glEnd();

    glColor3f(1,0,0);
    glBegin(GL_TRIANGLES); 
        // Seta +Z
        glNormal3f(0.0, 1.0, 0.0); 
        glVertex3f(-5,0,0);
        glVertex3f(0,0,100);
        glVertex3f(5,0,0);
    glEnd();

    glColor3f(0,0,1);
    glBegin(GL_TRIANGLES); 
        // Seta +X
        glNormal3f(0.0, 1.0, 0.0); 
        glVertex3f(0,0,-5);
        glVertex3f(100,0,0);
        glVertex3f(0,0,5);
    glEnd();
}

void World::drawChao(){ 
    glColor3f(1,1,1);
    glBegin(GL_QUADS); 
        glNormal3f(0.0, 1.0, 0.0); 
        glVertex3f(-FLOOR_SIZE/2,-1,-FLOOR_SIZE/2);
        glVertex3f(-FLOOR_SIZE/2,-1,+FLOOR_SIZE/2);
        glVertex3f(+FLOOR_SIZE/2,-1,+FLOOR_SIZE/2);
        glVertex3f(+FLOOR_SIZE/2,-1,-FLOOR_SIZE/2);
    glEnd();
}

void World::drawParedes(){
    glColor3f(0,0,1);
    glBegin(GL_QUADS);
        glNormal3f(1.0, 0.0, 0.0); 
        glVertex3f(-FLOOR_SIZE/2,-1,-FLOOR_SIZE/2);
        glVertex3f(-FLOOR_SIZE/2,-1,+FLOOR_SIZE/2);
        glVertex3f(-FLOOR_SIZE/2,SKY_HEIGHT,+FLOOR_SIZE/2);
        glVertex3f(-FLOOR_SIZE/2,SKY_HEIGHT,-FLOOR_SIZE/2);

        // glVertex3f(+FLOOR_SIZE/2,-1,+FLOOR_SIZE/2);
        // glVertex3f(+FLOOR_SIZE/2,-1,-FLOOR_SIZE/2);
    glEnd();

    glColor3f(0,0,1);
    glBegin(GL_QUADS);
        glNormal3f(0.0, 0.0, 1.0); 
        glVertex3f(+FLOOR_SIZE/2,-1,-FLOOR_SIZE/2);
        glVertex3f(-FLOOR_SIZE/2,-1,-FLOOR_SIZE/2);
        glVertex3f(-FLOOR_SIZE/2,SKY_HEIGHT,-FLOOR_SIZE/2);
        glVertex3f(+FLOOR_SIZE/2,SKY_HEIGHT,-FLOOR_SIZE/2);
    glEnd();
}
void World::drawCeu(){ }

GLdouble* expande(Matrix3x3& rot){
    GLdouble* mat = new GLdouble [16];
    mat[0] = rot.D00;
    mat[1] = rot.D10;
    mat[2] = rot.D20;
    mat[3] = 0;

    mat[4] = rot.D01;
    mat[5] = rot.D11;
    mat[6] = rot.D21;
    mat[7] = 0;

    mat[8] = rot.D02;
    mat[9] = rot.D12;
    mat[10] = rot.D22;
    mat[11] = 0;

    mat[12] = 0;
    mat[13] = 0;
    mat[14] = 0;
    mat[15] = 1;
    return mat; 
}

void World::draw(){
    glColor3f(1,1,1);
    // glutSolidTeapot(50.0f);
    // glutWireCube(80.0f);
    drawGeradores();
    drawChao();
    drawParedes();
    drawCeu();
    bando->draw();

    glPushMatrix();
    glTranslatef(100.0f, 100.0f, 100.0f);
    Quaternion q1 = Quaternion::FromAngleAxis(-M_PI/2,Vector3(1,0,0));
    Quaternion q2 = Quaternion::FromAngleAxis(-M_PI/3,Vector3(0,1,0));
    Quaternion q3 = q2 * q1;
    Matrix3x3 m1 = Matrix3x3::FromQuaternion(q3);
    
    glMultMatrixd(expande(m1));
    // Some other transformations
    

    // Draw something, i.e. cube
    glColor3f(1,0,1);
    glutSolidCone(40,80,10,15);

    glPopMatrix();
}

void World::update(){
    bando->update();
}

void World::view(){
	// Especifica posição do observador e do alvo
    std::cout << "(view) O:" <<  observador << "; A: " << alvo << std::endl;
	gluLookAt(observador.x, observador.y, observador.z,
                    alvo.x,       alvo.y,       alvo.z,
             normalObsvd.x,   normalObsvd.y,   normalObsvd.z);
}

void World::moveObservador(int frente, int direita, int cima){
    vec3 vetorFrente = alvo - observador;
    vetorFrente.normalizar();
    std::cout << "VF: " << vetorFrente << std::endl;
    if (frente > 0){
        observador += vetorFrente * PASSO;
        alvo += vetorFrente * PASSO;
    }else if (frente < 0){
        observador -= vetorFrente * PASSO;
        alvo -= vetorFrente * PASSO;
    }

    if (direita > 0){
        vec3 vetorDireita = vetorFrente * normalObsvd;
        vetorDireita.normalizar();
        observador += vetorDireita * PASSO;
        // alvo += vetorDireita * PASSO;
        std::cout << "VD: " << vetorDireita << std::endl;
    }else if (direita < 0){
        vec3 vetorEsquerda = normalObsvd * vetorFrente;
        vetorEsquerda.normalizar();
        observador += vetorEsquerda * PASSO;
        // alvo += vetorEsquerda * PASSO;
        std::cout << "VE: " << vetorEsquerda << std::endl;
    }

    vec3 vetorCima = normalObsvd;
    vetorCima.normalizar();
    std::cout << "VC: " << vetorCima << std::endl;
    if (cima > 0){
        observador += vetorCima * PASSO;
        alvo += vetorCima * PASSO;
        std::cout << "CIMA" << std::endl;
        std::cout << "(move) O:" <<  observador << "; A: " << alvo << std::endl;
    }else if (cima < 0){
        observador -= vetorCima * PASSO;
        alvo -= vetorCima * PASSO;
    }
    std::cout << std::endl;
}

void World::reset(){
    this->observador = vec3(0, 500, 1000);
    this->alvo = vec3(0, 0 ,0);
    this->normalObsvd = vec3(0, 1, 0);
}

void World::addBoid(){
    bando->addBoid();
}
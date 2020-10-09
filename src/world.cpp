#include "GL/glut.h"
#include "GL/gl.h"
#include <iostream>

#include "Matrix3x3.hpp"
#include "Quaternion.hpp"

#include "world.h"
#include "bando.h"
#include "utils.h"

World::World(){
    this->reset();
    bando = std::make_shared<Bando>(Vector3(15,150,150));
    bando->addBoid();
    fogEnabled = false;
}

World::World(const World& old){
    this->alvo = old.alvo;
    this->observador = old.observador;
    this->normalObsvd = old.normalObsvd;
    this->bando = old.bando;
    fogEnabled = false;
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


void World::draw(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(1,1,1);
    // glutSolidTeapot(50.0f);
    // glutWireCube(80.0f);
    drawGeradores();
    drawChao();
    drawParedes();
    drawCeu();
    // bando->draw();

    glPushMatrix();
    // Quaternion qx = Quaternion::FromAngleAxis(0,Vector3(1,0,0));
    // Quaternion qy = Quaternion::FromAngleAxis(-M_PI/3,Vector3(0,1,0));
    // Quaternion qz = Quaternion::FromAngleAxis(-M_PI/3,Vector3(0,1,0));
    // Quaternion q = qx * qz *qy;
    // Matrix3x3 m1 = Matrix3x3::FromQuaternion(q);
    
    // glMultMatrixd(expande(m1));
    // Some other transformations
    

    // Draw something, i.e. cube
    bando->draw();
    glPopMatrix();

    Torre t1(Vector3(0,0,0), 500, 100);
    t1.draw();
}

void World::update(){
    bando->update();
}

void World::addSeparacao(double delta){
    bando->addSeparacao(delta);
}
void World::addVelLocal(double delta){
    bando->addVelLocal(delta);
}
void World::addCampoVisao(double delta){
    bando->addCampoVisao(delta);
}
void World::view(){
	// Especifica posição do observador e do alvo
    // std::cout << "(view) O:" <<  observador << "; A: " << alvo << std::endl;
    glLoadIdentity();
	gluLookAt(observador.x, observador.y, observador.z,
                    alvo.x,       alvo.y,       alvo.z,
             normalObsvd.x,   normalObsvd.y,   normalObsvd.z);
    // Vector3 posLider = bando->getLiderPos();
    // Vector3 menosV = -300 * (Vector3::Normalized(bando->getLiderVel()));
    // Vector3 obs = posLider + menosV;
    // Vector3 normal = Vector3::Normalized(bando->getLiderNor());
    // obs += 100 * (normal);
    // gluLookAt(obs.X, obs.Y, obs.Z,
    //             posLider.X,   posLider.Y,   posLider.Z,
    //          normal.X,   normal.Y,   normal.Z);
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

void World::liderYawEsq(){
    bando->liderYawEsq();
}

void World::liderYawDir(){
    bando->liderYawDir();
}

void World::liderPitchUp(){
    bando->liderPitchUp();
}
void World::liderPitchDown(){
    bando->liderPitchDown();
}


void World::reset(){
    // this->observador = vec3(1500, 1000, 2500);
    this->observador = vec3(500, 250, 1000);
    this->alvo = vec3(300, 150 ,0);
    this->normalObsvd = vec3(0, 1, 0);
}

void World::toggleFog(){
    if (fogEnabled){
        fogEnabled = false;
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glDisable(GL_FOG);
    }else{
        fogEnabled = true;
        glClearColor(0.5, 0.5, 0.5, 1.0);  /* fog color */
        glEnable(GL_FOG);
    }
}

void World::addBoid(){
    bando->addBoid();
}

void World::removeBoid(){
    bando->removeBoid();
}
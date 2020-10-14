#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <iostream>

#include <Matrix3x3.hpp>
#include <Quaternion.hpp>

#include "utils.h"
#include "world.h"
#include "bando.h"

extern GLfloat angle;

World::World(){
    bando = std::make_shared<Bando>(Vector3(15,700,150));
    bando->addBoid();
    createObstaculos();

    fogEnabled = false;
    cameraAtual = AltoTorre;

    double towerH = 500;
    this->observador = Vector3(0, towerH + towerH/1.5 + 50, 0);
    this->alvo = bando->getCentroBando();
    this->normalObsvd = Vector3(0, 1, 0);
}

void World::createObstaculos(){
    double towerH = 500;
    obstaculos.push_back(std::make_shared<Torre>(Vector3(0,0,0), towerH, 100));

    obstaculos.push_back(std::make_shared<Torre>(Vector3(700,0,700), 300, 50));
    obstaculos.push_back(std::make_shared<Torre>(Vector3(700,0,800), 300, 50));
    obstaculos.push_back(std::make_shared<Torre>(Vector3(700,0,900), 300, 50));
    obstaculos.push_back(std::make_shared<Torre>(Vector3(700,0,1000), 300, 50));
    obstaculos.push_back(std::make_shared<Torre>(Vector3(700,0,1100), 300, 50));

    obstaculos.push_back(std::make_shared<Esfera>(Vector3(-1500,600,700)));
    obstaculos.push_back(std::make_shared<Esfera>(Vector3(-1400,400,800)));
    obstaculos.push_back(std::make_shared<Esfera>(Vector3(-1300,600,900)));
    obstaculos.push_back(std::make_shared<Esfera>(Vector3(-1200,400,1000)));
    obstaculos.push_back(std::make_shared<Esfera>(Vector3(-1100,600,1100)));

    obstaculos.push_back(std::make_shared<Torre>(Vector3(1250,0,700), 200, 40));
    obstaculos.push_back(std::make_shared<Torre>(Vector3(600,0,1700), 200, 40));
    obstaculos.push_back(std::make_shared<Torre>(Vector3(1600,0,1700), 200, 40));
    obstaculos.push_back(std::make_shared<Torre>(Vector3(-1600,0,-700), 200, 40));
    obstaculos.push_back(std::make_shared<Torre>(Vector3(-1900,0,-100), 200, 40));
    obstaculos.push_back(std::make_shared<Torre>(Vector3(-400,0,-700), 200, 40));

    std::vector<std::shared_ptr<Obstaculo>>::iterator it;
    for (it = obstaculos.begin(); it != obstaculos.end(); it++){
        bando->addObstaculo(*it);
    }
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
    glColor3f(0,0.65,0.41);
    glBegin(GL_QUADS); 
        glNormal3f(0.0, 1.0, 0.0); 
        glVertex3f(-FLOOR_SIZE/2,-1,-FLOOR_SIZE/2);
        glVertex3f(-FLOOR_SIZE/2,-1,+FLOOR_SIZE/2);
        glVertex3f(+FLOOR_SIZE/2,-1,+FLOOR_SIZE/2);
        glVertex3f(+FLOOR_SIZE/2,-1,-FLOOR_SIZE/2);
    glEnd();
}

void World::drawCeu(){
    if (fogEnabled){
        glClearColor(0.5, 0.5, 0.5, 1);
    }else{
        glClearColor(0.529, 0.808, 0.922, 1);
    }
}

void World::draw(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    drawCeu();
    drawGeradores();
    drawChao();

    glPushMatrix();
    bando->draw();
    glPopMatrix();

    std::vector<std::shared_ptr<Obstaculo>>::iterator it;
    for (it = obstaculos.begin(); it != obstaculos.end(); it++){
        (*it)->draw();
    }
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
void World::changeCamera(Camera newCamera){
    cameraAtual = newCamera;
    angle = 45;
}

void World::view(){
	// Especifica posição do observador e do alvo
    // std::cout << "(view) O:" <<  observador << "; A: " << alvo << std::endl;
    glLoadIdentity();
	
    switch (cameraAtual){
        case Chase:{
            Vector3 posLider = bando->getLiderPos();
            Vector3 menosV = -FATOR_LIDER_CAM_OFFSET_HORZ * \
                             (Vector3::Normalized(bando->getLiderVel()));
            Vector3 obs = posLider + menosV;
            Vector3 normal = Vector3::Normalized(bando->getLiderNor());
            obs += FATOR_LIDER_CAM_OFFSET_VERT * normal;

            gluLookAt(     obs.X,      obs.Y,      obs.Z,       // Pos. Observ.
                      posLider.X, posLider.Y, posLider.Z,       // Pos. Alvo
                        normal.X,   normal.Y,   normal.Z);      // Normal Obsv.
            break;
        }case ChaseLateral:{
            Vector3 posLider = bando->getLiderPos();
            Vector3 vel = Vector3::Normalized(bando->getLiderVel());
            Vector3 normal = Vector3::Normalized(bando->getLiderNor());
            Vector3 esquerda = Vector3::Cross(normal, vel);
            Vector3 obs = posLider + FATOR_LIDER_CAM_OFFSET_HORZ * esquerda;

            gluLookAt(     obs.X,      obs.Y,      obs.Z,       // Pos. Observ.
                      posLider.X, posLider.Y, posLider.Z,       // Pos. Alvo
                        normal.X,   normal.Y,   normal.Z);      // Normal Obsv.
            break;
        }case AltoTorre:{
            alvo = bando->getCentroBando();
            gluLookAt( observador.X,  observador.Y,  observador.Z,  // Pos. Observ.
                             alvo.X,        alvo.Y,        alvo.Z,  // Pos. Alvo
                      normalObsvd.X, normalObsvd.Y, normalObsvd.Z); // Normal Obsv.
            break;
        }
    }
    
}

void World::moveObservador(int frente, int direita, int cima){
    Vector3 vetorFrente = alvo - observador;
    vetorFrente = Vector3::Normalized(vetorFrente);
    if (frente > 0){
        observador += vetorFrente * PASSO;
        alvo += vetorFrente * PASSO;
    }else if (frente < 0){
        observador -= vetorFrente * PASSO;
        alvo -= vetorFrente * PASSO;
    }

    if (direita > 0){
        Vector3 vetorDireita = Vector3::Cross(vetorFrente, normalObsvd);
        vetorDireita = Vector3::Normalized(vetorDireita);
        observador += vetorDireita * PASSO;
        // alvo += vetorDireita * PASSO;
    }else if (direita < 0){
        Vector3 vetorEsquerda = Vector3::Cross(normalObsvd, vetorFrente);
        vetorEsquerda = Vector3::Normalized(vetorEsquerda);
        observador += vetorEsquerda * PASSO;
        // alvo += vetorEsquerda * PASSO;
    }

    Vector3 vetorCima = normalObsvd;
    vetorCima = Vector3::Normalized(vetorCima);
    if (cima > 0){
        observador += vetorCima * PASSO;
        alvo += vetorCima * PASSO;
    }else if (cima < 0){
        observador -= vetorCima * PASSO;
        alvo -= vetorCima * PASSO;
    }
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
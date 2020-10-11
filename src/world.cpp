#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <iostream>

#include <Matrix3x3.hpp>
#include <Quaternion.hpp>

#include "world.h"
#include "bando.h"
#include "utils.h"

extern GLfloat angle;

World::World(){
    this->reset();

    bando = std::make_shared<Bando>(Vector3(15,150,150));
    bando->addBoid();
    obstaculos.push_back(std::make_shared<Esfera>(Vector3(100,150,-150)));
    bando->addObstaculo(obstaculos[0]);

    fogEnabled = false;
    cameraAtual = AltoTorre;
    zoomFactor = 1;
}

World::World(const World& old){
    this->alvo = old.alvo;
    this->observador = old.observador;
    this->normalObsvd = old.normalObsvd;
    this->bando = old.bando;
    fogEnabled = false;
    cameraAtual = AltoTorre;
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
            Vector3 menosV = -300 * (Vector3::Normalized(bando->getLiderVel()));
            Vector3 obs = posLider + menosV;
            Vector3 normal = Vector3::Normalized(bando->getLiderNor());
            obs += 100 * (normal);

            gluLookAt(obs.X, obs.Y, obs.Z,
                        posLider.X,   posLider.Y,   posLider.Z,
                    normal.X,   normal.Y,   normal.Z);
            break;
        }case ChaseLateral:{
            gluLookAt(observador.X, observador.Y, observador.Z,
                    alvo.X,       alvo.Y,       alvo.Z,
             normalObsvd.X,   normalObsvd.Y,   normalObsvd.Z);
            break;
        }case AltoTorre:{
            gluLookAt(observador.X, observador.Y, observador.Z,
                    alvo.X,       alvo.Y,       alvo.Z,
             normalObsvd.X,   normalObsvd.Y,   normalObsvd.Z);
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


void World::reset(){
    // this->observador = vec3(1500, 1000, 2500);
    this->observador = Vector3(500, 250, 1000);
    this->alvo = Vector3(300, 150 ,0);
    this->normalObsvd = Vector3(0, 1, 0);
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
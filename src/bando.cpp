#include <iostream>
#include "bando.h"
#include "constants.h"

Bando::Bando(Vector3 _posleader){
    pos = _posleader;
    lider = std::make_shared<BoidLider>(_posleader);

    inicio = 0;
    fim = 0;
    dir = 0;
    esq = 0;
    i = 20;
}

void drawVector(Vector3 vec, Vector3 origem){
    Vector3 copy = vec;
    // if (Vector3::Magnitude(copy) >= 100){
    //     copy = Vector3::Normalized(copy);
    //     copy = copy * 5;
    // }
    // if (Vector3::Magnitude(copy) <= 100){
    //     copy = Vector3::Normalized(copy);
    //     copy = copy * 5;
    // }
    copy = copy * 20;
    glColor3f(1,0,0);
    glBegin(GL_TRIANGLES); 
        glNormal3f(0.0, 1.0, 0.0); 
        glVertex3f(origem.X, origem.Y - 1, origem.Z);
        glVertex3f(origem.X + copy.X, origem.Y + copy.Y, origem.Z + copy.Z);
        glVertex3f(origem.X, origem.Y + 1, origem.Z);
    glEnd();
}

void Bando::draw(){
    lider->draw();
    std::vector<std::shared_ptr<BoidComum>>::iterator it;
    for (it = bando.begin(); it != bando.end(); it++){
        (*it)->draw();
        drawVector((*it)->velocity, (*it)->pos + Vector3(30,0,0));
        drawVector((*it)->frente, (*it)->pos + Vector3(30,30,0));
    }
}



void Bando::update(){
    // Computa a velocidade para cada boid com base nas regras
    std::vector<std::shared_ptr<BoidComum>>::iterator it;
    for (it = bando.begin(); it != bando.end(); it++){
        Vector3 v1, v2, v3;
        std::shared_ptr<Boid> bAtual = *it;

        v1 = Vector3(0,0,1);
        // v1 = regra1();
        // v2 = regra2();
        // v3 = regra3();

        Vector3 soma = v1 + v2 + v3;
        bAtual->addVelocity(soma);
    }
    
    // Muda a posição de cada boid
    lider->update();
    for (it = bando.begin(); it != bando.end(); it++){
        (*it)->update();
    }
}

void Bando::addBoid(){
    std::srand(time(NULL));
    GLfloat x = pos.X - 30 - fim - (std::rand()%(MAX_DIST_SPAWN_BOID - MIN_DIST_BOID) + MIN_DIST_BOID);

    GLfloat y = pos.Y + std::rand()%(MAX_DIST_SPAWN_BOID - MIN_DIST_BOID) + MIN_DIST_BOID;

    GLfloat z = pos.Z + esq + std::rand()%(MAX_DIST_SPAWN_BOID - MIN_DIST_BOID) + MIN_DIST_BOID;

    fim = x - 30;
    esq = z;

    std::shared_ptr<BoidComum> b = std::make_shared<BoidComum>(Vector3(x, y, z));
    bando.push_back(b);
}
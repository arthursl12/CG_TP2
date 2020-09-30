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

void Bando::draw(){
    lider->draw();
    std::vector<std::shared_ptr<BoidComum>>::iterator it;
    for (it = bando.begin(); it != bando.end(); it++){
        (*it)->draw();
    }
}

void Bando::update(){
    GLfloat raioLong = esq - dir;
    std::cout << raioLong << std::endl;

    std::vector<std::shared_ptr<BoidComum>>::iterator it;
    GLfloat maxDir = 0;
    for (it = bando.begin(); it != bando.end(); it++){
        Vector3 vecDist = (*it)->pos - lider->pos;
        GLfloat dist = Vector3::Magnitude(vecDist);
        if (dist > maxDir){
            maxDir = dist;
        }
    }

    std::cout << maxDir << std::endl;
    // Rearranja

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
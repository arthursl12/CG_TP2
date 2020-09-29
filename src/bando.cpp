#include <iostream>
#include "bando.h"

Bando::Bando(vec3 _posleader){
    pos = _posleader;
    lider = std::make_shared<BoidLider>(_posleader);

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
    lider->update();
    std::vector<std::shared_ptr<BoidComum>>::iterator it;
    for (it = bando.begin(); it != bando.end(); it++){
        (*it)->draw();
    }
}

void Bando::addBoid(){
    std::srand(time(NULL));
    std::shared_ptr<BoidComum> b = std::make_shared<BoidComum>(vec3(30 + std::rand()%i,30,-10));
    bando.push_back(b);
    i += 10;
}
#include "bando.h"


Bando::Bando(vec3 _posleader){
    pos = _posleader;
    lider = std::make_shared<Boid>(_posleader);
}

void Bando::draw(){
    lider->draw();
    std::vector<std::shared_ptr<Boid>>::iterator it;
    for (it = bando.begin(); it != bando.end(); it++){
        (*it)->draw();
    }
}
void Bando::update(){
    lider->update();
    std::vector<std::shared_ptr<Boid>>::iterator it;
    for (it = bando.begin(); it != bando.end(); it++){
        (*it)->draw();
    }
}
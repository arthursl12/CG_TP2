#include <Quaternion.hpp>
#include "constants.h"
#include "utils.h"
#include "piramide.h"
#include "boid.h"


Boid::Boid(Vector3 _pos){
    pos = _pos;

    frente = Vector3(1,0,0);
    velocity = Vector3(1,0,0);
    cima = Vector3(0,1,0);
    esq = Vector3(0,0,-1);

    flapTimer = 0;
}

void Boid::update(){
    double passo = BOID_PASSO;
    if (DBG) passo = passo;
    pos += velocity * passo;
    flapTimer += 1;

    if (flapTimer >= WING_FLAP_INTERVAL){
        flapTimer = 0;
    }
}

bool Boid::operator!=(Boid& outro){
    Vector3 vecDist = this->pos - outro.pos;
    double dist = Vector3::Magnitude(vecDist);

    if (dist >= 1){
        return true;
    }else{
        return false;
    }
}




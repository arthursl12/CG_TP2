#include "GL/glut.h"
#include <iostream>

#include "world.h"

World::World() :
    observador(0, 100, 200),
    alvo(0, 0 ,0)
{
}

void World::draw(){
    glutSolidTeapot(50.0f);
}

void World::view(){
	// Especifica posição do observador e do alvo
    std::cout << observador << std::endl;
	gluLookAt(observador.x, observador.y, observador.z,
                    alvo.x,       alvo.y,       alvo.z,
                0,   1,   0);
}

void World::moveObservador(int frente, int lado, int vertical){
    vec3 vetorFrente = alvo - observador;
    vetorFrente.normalizar();

    if (frente > 0){
        observador += vetorFrente;
    }else if (frente < 0){
        observador -= vetorFrente;
    }
    // if (y){
    //     observador.y = observador.y + 1 * PASSO;
    // }
    // if (z){
    //     observador.z = observador.z + 1 * PASSO;
    // }
}
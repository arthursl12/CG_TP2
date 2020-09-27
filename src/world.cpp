#include "GL/glut.h"
#include <iostream>

#include "world.h"

World::World(){
    this->reset();
}

World::World(const World& old){
    this->alvo = old.alvo;
    this->observador = old.observador;
    this->normalObsvd = old.normalObsvd;
}

void World::draw(){
    glutSolidTeapot(50.0f);
    glutWireCube(80.0f);

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
        alvo += vetorDireita * PASSO;
        std::cout << "VD: " << vetorDireita << std::endl;
    }else if (direita < 0){
        vec3 vetorEsquerda = normalObsvd * vetorFrente;
        vetorEsquerda.normalizar();
        observador += vetorEsquerda * PASSO;
        alvo += vetorEsquerda * PASSO;
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
    this->observador = vec3(0, 100, 200);
    this->alvo = vec3(0, 0 ,0);
    this->normalObsvd = vec3(0, 1, 0);
}
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

/**
 * Um boid se move com velocidade e direção similares aos boids que ele consegue
 * ter em seu campo de visão 
 *
 * https://github.com/beneater/boids/blob/86b4cb9896f43d598867b7d58986210ba21f03de/boids.js#L116
 * 
 */
Vector3 Bando::velocidadesSimilares(Boid& b){
    Vector3 vNotada = Vector3::Zero();
    int qtdProximos = 0;

    std::vector<std::shared_ptr<BoidComum>>::iterator it;
    for (it = bando.begin(); it != bando.end(); it++){
        Vector3 vecDist = b.pos - (*it)->pos;
        double dist = Vector3::Magnitude(vecDist);

        if (dist < CAMPO_VISAO){
            vNotada += (*it)->velocity;
            qtdProximos++;
        }
    }

    if (qtdProximos > 0){
        vNotada = vNotada/qtdProximos;
        return vNotada * FATOR_VEL_LOCAL;
    }else{
        return Vector3::Zero();
    }
}


void Bando::update(){
    // Computa a velocidade para cada boid com base nas regras
    std::vector<std::shared_ptr<BoidComum>>::iterator it;
    for (it = bando.begin(); it != bando.end(); it++){
        std::srand(time(NULL));
        Vector3 v1, v2, v3;
        std::shared_ptr<Boid> bAtual = *it;

        // if (std::rand()%100 > 50){
        //     v1 = Vector3(-0.004,0,0.00002);
        // }else if(std::rand()%100 > 50){
        //     v2 = Vector3(0.002,0,-0.00001);
        // }
            
        // v1 = regra1();
        // v2 = regra2();
        v3 = velocidadesSimilares(*bAtual);

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
    x *= pow(-1, std::rand()%2);
    y *= pow(-1, std::rand()%2);
    z *= pow(-1, std::rand()%2);
    b->addVelocity(Vector3((int)x%2, (int)y%4, (int)z%5));
    bando.push_back(b);
}
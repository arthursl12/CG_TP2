#include <iostream>
#include "bando.h"
#include "constants.h"

Bando::Bando(Vector3 _posleader){
    pos = _posleader;
    lider = std::make_shared<BoidLider>(_posleader);

    fatCentro = FATOR_CENTRALIZAR_INI;
    fatCurva = FATOR_CURVA_INI;
    fatVelLoc = FATOR_VEL_LOCAL_INI;
    fatSeparar = FATOR_SEPARACAO_INI;
    fatLider = 0.0001;
    campoVisao = CAMPO_VISAO_INI;
}

Vector3 Bando::getLiderPos(){
    return lider->pos;
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
        // drawVector((*it)->frente, (*it)->pos + Vector3(30,30,0));
    }
    // drawVector(centroBando, Vector3(0,0,0));
}

void Bando::addSeparacao(double delta){
    fatSeparar += delta;
    if (fatSeparar <= FATOR_SEPARACAO_MIN){
        fatSeparar = FATOR_SEPARACAO_MIN;
    }else if (fatSeparar >= FATOR_SEPARACAO_MAX){
        fatSeparar = FATOR_SEPARACAO_MAX;
    }
}

void Bando::addVelLocal(double delta){
    fatVelLoc += delta;
    if (fatVelLoc <= FATOR_VEL_LOCAL_MIN){
        fatVelLoc = FATOR_VEL_LOCAL_MIN;
    }else if(fatVelLoc >= FATOR_VEL_LOCAL_MAX){
        fatVelLoc = FATOR_VEL_LOCAL_MAX;
    }
}

void Bando::addCampoVisao(double delta){
    campoVisao += delta;
    if (campoVisao <= 0){
        campoVisao = 0;
    }
    // else if(fatCurva >= FATOR_CURVA_MAX){
    //     fatCurva = FATOR_CURVA_MAX;
    // }
}

/**
 * ALINHAMENTO :
 * Um boid se move com velocidade e direção similares aos boids que ele consegue
 * ter em seu campo de visão 
 *
 * Adaptado de:
 * https://github.com/beneater/boids/blob/86b4cb9896f43d598867b7d58986210ba21f03de/boids.js#L116
 */
Vector3 Bando::velocidadesSimilares(Boid& b){
    Vector3 vNotada = Vector3::Zero();
    int qtdProximos = 0;

    std::vector<std::shared_ptr<BoidComum>>::iterator it;
    for (it = bando.begin(); it != bando.end(); it++){
        Vector3 vecDist = b.pos - (*it)->pos;
        double dist = Vector3::Magnitude(vecDist);

        if (dist < campoVisao){
            vNotada += (*it)->velocity;
            qtdProximos++;
        }
    }

    if (qtdProximos > 0){
        vNotada = vNotada/qtdProximos;
        return vNotada * fatVelLoc;
    }else{
        return Vector3::Zero();
    }
}

/**
 * Manter os boids dentro da "caixa", evitar que saiam de onde conseguimos
 * vê-los
 *
 * Adaptado de:
 * https://github.com/beneater/boids/blob/86b4cb9896f43d598867b7d58986210ba21f03de/boids.js#L51
 */
Vector3 Bando::manterLimites(Boid& b){
    Vector3 pos = b.pos;
    Vector3 vel = Vector3::Zero();

    
    // Eixo X
    if (pos.X < (-FLOOR_SIZE/2) + BOID_OFFSET_MARGIN) {
        vel.X += fatCurva;
    }
    if (pos.X > FLOOR_SIZE/2 - BOID_OFFSET_MARGIN) {
        vel.X -= fatCurva;
    }

    // Eixo Y (altura)
    if (pos.Y < BOID_OFFSET_MARGIN) {
        vel.Y += fatCurva;
    }
    if (pos.Y > SKY_HEIGHT - BOID_OFFSET_MARGIN) {
        vel.Y -= fatCurva;
    }

    // Eixo Z
    if (pos.Z < (-FLOOR_SIZE/2) + BOID_OFFSET_MARGIN) {
        vel.Z += fatCurva;
    }
    if (pos.Z > FLOOR_SIZE/2 - BOID_OFFSET_MARGIN) {
        vel.Z -= fatCurva;
    }

    return vel;
}

/**
 * COESÃO :
 * Um boid tende a ficar junto com os boids em seu campo de visão. Isso pode 
 * ser modelado somando à sua velocidade um fator que tende ao "centro de massa"
 * dos boids ao redor dele. 
 *
 * Adaptado de:
 * https://github.com/beneater/boids/blob/86b4cb9896f43d598867b7d58986210ba21f03de/boids.js#L71
 */
Vector3 Bando::voarParaCentro(Boid& b){
    Vector3 centro = Vector3::Zero();
    int qtdProximos = 0;
    
    std::vector<std::shared_ptr<BoidComum>>::iterator it;
    for (it = bando.begin(); it != bando.end(); it++){
        Vector3 vecDist = b.pos - (*it)->pos;
        double dist = Vector3::Magnitude(vecDist);

        if (b != **it && dist <= campoVisao){
            centro += (*it)->pos;
            qtdProximos++;
        }
    }

    if (qtdProximos > 0){
        centro = centro/qtdProximos;
        return centro * fatCentro;
    }else{
        return Vector3::Zero();
    }
}

/**
 * SEPARAÇÃO :
 * Um boid tende a manter uma distância mínima entre ele e outros boids
 *
 * Adaptado de:
 * https://github.com/beneater/boids/blob/86b4cb9896f43d598867b7d58986210ba21f03de/boids.js#L96
 */
Vector3 Bando::manterDistanciaOutros(Boid& b){
    Vector3 velEvitar = Vector3::Zero();

    std::vector<std::shared_ptr<BoidComum>>::iterator it;
    for (it = bando.begin(); it != bando.end(); it++){
        if (b != (**it)){
            Vector3 vecDist = b.pos - (*it)->pos;
            double dist = Vector3::Magnitude(vecDist);

            if (dist < MIN_DIST){
                velEvitar += b.pos - (*it)->pos;
            }
        }
    }

    return velEvitar * fatSeparar;
}   

/**
 * Um boid tende a seguir o boid líder
 *
 * Adaptado de:
 * http://www.kfish.org/boids/pseudocode.html
 */
Vector3 Bando::seguirLider(Boid& b){
    Vector3 liderPos = lider->pos;
    return (liderPos - b.pos) * fatLider;
}

void Bando::update(){
    // Computa a velocidade para cada boid com base nas regras
    std::vector<std::shared_ptr<BoidComum>>::iterator it;
    for (it = bando.begin(); it != bando.end(); it++){
        std::srand(time(NULL));
        Vector3 v1, v2, v3, v4, v5;
        std::shared_ptr<Boid> bAtual = *it;
            
        v1 = voarParaCentro(*bAtual);           // Coesão
        v2 = manterDistanciaOutros(*bAtual);    // Separação
        v3 = velocidadesSimilares(*bAtual);     // Alinhamento
        v4 = seguirLider(*bAtual);
        v5 = manterLimites(*bAtual);

        Vector3 soma = v1 + v2 + v3 + v4 + v5;
        bAtual->addVelocity(soma);
    }
    std::cout << "CV:" << campoVisao << ", VLoc: " << fatVelLoc << ", Sepa: " << fatSeparar << std::endl;


    // Muda a posição de cada boid
    lider->update();
    for (it = bando.begin(); it != bando.end(); it++){
        (*it)->update();
    }
}

/**
 * Spawna um boid novo próximo ao bando
 */
void Bando::addBoid(){
    std::srand(time(NULL));
    Vector3 newPos = Vector3::Zero();
    if (bando.size() == 0){
        newPos.X += std::rand() % 40;
        newPos.Y += std::rand() % 20;
        newPos.Z += std::rand() % 40;
    }else{
        std::vector<std::shared_ptr<BoidComum>>::iterator randIt = bando.begin();
        std::advance(randIt, std::rand() % bando.size());
        BoidComum boid = **randIt;

        newPos = boid.pos;
        newPos.X += (std::rand() % 2 == 0) ? std::rand() % 60 : -std::rand() % 60;
        newPos.Y += (std::rand() % 2 == 0) ? std::rand() % 40 : -std::rand() % 40;
        newPos.Z += (std::rand() % 2 == 0) ? std::rand() % 60 : -std::rand() % 60;
    }

    
    std::shared_ptr<BoidComum> b = std::make_shared<BoidComum>(newPos);
    bando.push_back(b);
}
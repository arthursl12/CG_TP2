#include <GL/gl.h>
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
Vector3 Bando::getLiderVel(){
    return lider->velocity;
}
Vector3 Bando::getLiderNor(){
    return lider->cima;
}

void Bando::liderYawEsq(){
    lider->yawEsq();
}
void Bando::liderYawDir(){
    lider->yawDir();
}
void Bando::liderPitchUp(){
    lider->pitchUp();
}
void Bando::liderPitchDown(){
    lider->pitchDown();
}
void Bando::liderRollEsq(){
    lider->rollEsq();
}
void Bando::liderRollDir(){
    lider->rollDir();
}

void drawVector(Vector3 vec, Vector3 origem){
    Vector3 copy = vec;
    copy = copy * 20;

    glBegin(GL_TRIANGLES); 
        glVertex3f(origem.X, origem.Y - 2, origem.Z - 2);
        glVertex3f(origem.X + copy.X, origem.Y + copy.Y, origem.Z + copy.Z);
        glVertex3f(origem.X, origem.Y + 2, origem.Z + 2);
    glEnd();
}

void Bando::draw(){
    lider->draw();
    glColor3f(1,1,0);
    drawVector(lider->cima, lider->pos + Vector3(30,0,0));
    glColor3f(1,0,0);
    drawVector(lider->velocity, lider->pos + Vector3(30,0,0));
    glColor3f(0,0.5,1);
    drawVector(lider->esq, lider->pos + Vector3(30,0,0));

    glColor3f(1,0,1);
    drawVector(lider->frente, lider->pos + Vector3(30,30,0));

    std::vector<std::shared_ptr<BoidComum>>::iterator it;
    for (it = bando.begin(); it != bando.end(); it++){
        (*it)->draw();
        drawVector((*it)->velocity, (*it)->pos + Vector3(30,0,0));
        drawVector((*it)->cima, (*it)->pos + Vector3(30,0,0));
    }
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
}

void Bando::addObstaculo(std::shared_ptr<Obstaculo> obs){
    obstaculos.push_back(obs);
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
 * Adaptado de: <br> 
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
 * dos boids ao redor dele, sendo que ele não é incluído para o cálculo desse
 * "centro de massa". 
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
 * Um pode tender para um determinado lugar (por exemplo para o boid líder, 
 * seguindo-o).
 *
 * Adaptado de:
 * http://www.kfish.org/boids/pseudocode.html
 */
Vector3 Bando::tenderPara(Boid& b, Vector3 _pos){
    return (_pos - b.pos) * fatLider;
}

void Bando::update(){
    // Computa a velocidade para cada boid com base nas regras
    std::vector<std::shared_ptr<BoidComum>>::iterator it;
    for (it = bando.begin(); it != bando.end(); it++){
        std::srand(time(NULL));
        Vector3 v1, v2, v3, v4, v5, v6, v7;
        std::shared_ptr<BoidComum> bAtual = *it;
        
        // Evitar obstáculos, se estiver perto o suficiente
        std::vector<std::shared_ptr<Obstaculo>>::iterator it1;
        bool flagObst = false;
        Vector3 v = Vector3::Zero();
        for (it1 = obstaculos.begin(); it1 != obstaculos.end(); it1++){
            if ((*it1)->proximo(bAtual->pos)){
                flagObst = true;
                v7 += -100 * tenderPara(*bAtual, (*it1)->maisProximo(bAtual->pos) );
            }
        }

        if (!flagObst){
            v1 = voarParaCentro(*bAtual);           // Coesão
            v2 = manterDistanciaOutros(*bAtual);    // Separação
            v3 = velocidadesSimilares(*bAtual);     // Alinhamento
            v4 = tenderPara(*bAtual, lider->pos);
            v6 = manterLimites(*bAtual);
        }
        Vector3 soma = v1 + v2 + v3 + v4 + v5 + v6 + v7;
        bAtual->addVelocity(soma);

    }
    // std::cout << "CV:" << campoVisao << ", VLoc: " << fatVelLoc << ", Sepa: " << fatSeparar << std::endl;

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
        newPos.X += std::rand() % 400 + 100;
        newPos.Y += std::rand() % 800 + 400;
        newPos.Z += std::rand() % 400 + 100;
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

/**
 * Remove um boid aleatório do bando, que deve ter sempre pelo menos um boid,
 * além do líder
 */
void Bando::removeBoid(){
    std::srand(time(NULL));
    if (bando.size() > 1){
        std::vector<std::shared_ptr<BoidComum>>::iterator randIt = bando.begin();
        std::advance(randIt, std::rand() % bando.size());
        bando.erase(randIt);
    }
}

/**
 * Calcula o centro do bando de Boids, considerando o líder também
 * @return Ponto do centro do bando
 */
Vector3 Bando::getCentroBando(){
    Vector3 centro = Vector3::Zero();
    std::vector<std::shared_ptr<BoidComum>>::iterator it;
    for (it = bando.begin(); it != bando.end(); it++){
        centro += (*it)->pos;
    }
    centro += lider->pos;

    int totalBoids = bando.size() + 1;
    centro = centro / totalBoids;
    return centro;
}
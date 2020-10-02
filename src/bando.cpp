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
        // drawVector((*it)->frente, (*it)->pos + Vector3(30,30,0));
    }
    // drawVector(centroBando, Vector3(0,0,0));
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
        vel.X += BOID_FATOR_CURVA;
    }
    if (pos.X > FLOOR_SIZE/2 - BOID_OFFSET_MARGIN) {
        vel.X -= BOID_FATOR_CURVA;
    }

    // Eixo Y (altura)
    if (pos.Y < BOID_OFFSET_MARGIN) {
        vel.Y += BOID_FATOR_CURVA;
    }
    if (pos.Y > SKY_HEIGHT - BOID_OFFSET_MARGIN) {
        vel.Y -= BOID_FATOR_CURVA;
    }

    // Eixo Z
    if (pos.Z < (-FLOOR_SIZE/2) + BOID_OFFSET_MARGIN) {
        vel.Z += BOID_FATOR_CURVA;
    }
    if (pos.Z > FLOOR_SIZE/2 - BOID_OFFSET_MARGIN) {
        vel.Z -= BOID_FATOR_CURVA;
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

        if (b != **it){
            centro += (*it)->pos;
            qtdProximos++;
        }
    }

    if (qtdProximos > 0){
        centro = centro/qtdProximos;
        return centro * FATOR_CENTRALIZAR;
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

    return velEvitar * FATOR_SEPARACAO;
}   

void Bando::update(){
    // Computa a velocidade para cada boid com base nas regras
    std::vector<std::shared_ptr<BoidComum>>::iterator it;
    for (it = bando.begin(); it != bando.end(); it++){
        std::srand(time(NULL));
        Vector3 v1, v2, v3, v4;
        std::shared_ptr<Boid> bAtual = *it;

        // if (std::rand()%100 > 50){
        //     v1 = Vector3(-0.004,0,0.00002);
        // }else if(std::rand()%100 > 50){
        //     v2 = Vector3(0.002,0,-0.00001);
        // }
            
        v1 = voarParaCentro(*bAtual);           // Coesão
        
        v2 = manterDistanciaOutros(*bAtual);    // Separação
        v3 = velocidadesSimilares(*bAtual);     // Alinhamento
        v4 = manterLimites(*bAtual);

        Vector3 soma = v1 + v2 + v3 + v4;
        bAtual->addVelocity(soma);
    }
    std::cout << "Centr:" << FATOR_CENTRALIZAR << ", Curva: " << BOID_FATOR_CURVA << ", VLoc: " << FATOR_VEL_LOCAL << ", Sepa: " << FATOR_SEPARACAO << std::endl;


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
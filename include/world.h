/**
 * Classe World.
 *
 * Gerencia todos os objetos e sua existência na cena
 *
 * @param 
 *      
 */

#ifndef WORLD_H
#define WORLD_H

#include "linalg.h"
#include "constants.h"
#include "bando.h"


class World{
    public:
        World();
        World(const World& old);
        void draw();
        void update();
        void view();

        void moveObservador(int frente, int direita, int cima);
        void reset();
        void addBoid();

        void addSeparacao(double delta);
        void addVelLocal(double delta);
        void addCampoVisao(double delta);

        void liderYawEsq();
    private:
        vec3 observador;
        vec3 alvo;
        vec3 normalObsvd;
        std::shared_ptr<Bando> bando;

        void drawGeradores();
        void drawChao();
        void drawParedes();
        void drawCeu();
};

#endif /* WORLD_H */
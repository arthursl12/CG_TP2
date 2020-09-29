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


class World{
    public:
        World();
        World(const World& old);
        void draw();
        void update();
        void view();

        void moveObservador(int frente, int direita, int cima);
        void reset();
    private:
        vec3 observador;
        vec3 alvo;
        vec3 normalObsvd;

        void drawGeradores();
};

#endif /* WORLD_H */
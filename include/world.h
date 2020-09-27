#ifndef WORLD_H
#define WORLD_H

#include "linalg.h"
#include "constants.h"


class World{
    private:
        vec3 observador;
        vec3 alvo;
        vec3 normalObsvd;

    public:
        World();
        World(const World& old);
        void draw();
        void update();
        void view();

        void moveObservador(int frente, int direita, int cima);
        void reset();
};

#endif /* WORLD_H */
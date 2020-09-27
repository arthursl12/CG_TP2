#ifndef WORLD_H
#define WORLD_H

#include "linalg.h"
#include "constants.h"


class World{
    private:
        vec3 observador;
        vec3 alvo;

    public:
        World();
        void draw();
        void update();
        void view();

        void moveObservador(int frente, int lado, int vertical);
};

#endif /* WORLD_H */
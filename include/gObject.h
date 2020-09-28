#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "linalg.h"
#include <string>

class GameObject {
    public:
        virtual void draw() = 0;
        virtual void update() = 0;
        std::string getNome();
    protected:
        vec3 pos;
        float height, width, depth;
        std::string nome;
};

#endif /* GAME_OBJECT_H */
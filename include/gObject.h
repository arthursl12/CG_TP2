#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <Vector3.hpp>
#include <string>

class GameObject {
    public:
        virtual void draw() = 0;
        virtual void update() = 0;
    protected:
        Vector3 pos;
};

#endif /* GAME_OBJECT_H */
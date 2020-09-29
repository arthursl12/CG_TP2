#ifndef BANDO_H
#define BANDO_H

#include <memory>
#include <vector>
#include "gObject.h"
#include "boid.h"

class Bando : public GameObject{
    public:
        Bando(vec3 _posleader);
        void draw();
        void update();
    private:
        std::shared_ptr<Boid> lider;
        std::vector<std::shared_ptr<Boid>> bando;
};

#endif

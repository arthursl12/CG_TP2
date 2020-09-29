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

        void addBoid();
    private:
        int i;

        std::shared_ptr<BoidLider> lider;
        std::vector<std::shared_ptr<BoidComum>> bando;

        GLfloat inicio;
        GLfloat fim;
        GLfloat dir;
        GLfloat esq;
};

#endif

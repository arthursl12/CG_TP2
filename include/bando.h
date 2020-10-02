#ifndef BANDO_H
#define BANDO_H

#include <memory>
#include <vector>
#include "gObject.h"
#include "boid.h"

class Bando : public GameObject{
    public:
        Bando(Vector3 _posleader);
        void draw();
        void update();

        void addBoid();
    private:
        int i;
        Vector3 centroBando;

        std::shared_ptr<BoidLider> lider;
        std::vector<std::shared_ptr<BoidComum>> bando;

        GLfloat inicio;
        GLfloat fim;
        GLfloat dir;
        GLfloat esq;

        const double FATOR_CENTRALIZAR = 0.0000005;
        const double BOID_FATOR_CURVA = 0.03;
        const double FATOR_VEL_LOCAL = 0.005;
        const double FATOR_SEPARACAO = 0.005;
        
        Vector3 voarParaCentro(Boid& b);
        Vector3 manterDistanciaOutros(Boid& b);
        Vector3 velocidadesSimilares(Boid& b);
        Vector3 manterLimites(Boid& b);
};

#endif

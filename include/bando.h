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
        void addSeparacao(double delta);
        void addVelLocal(double delta);
        void addCampoVisao(double delta);
    private:
        int i;
        Vector3 centroBando;

        std::shared_ptr<BoidLider> lider;
        std::vector<std::shared_ptr<BoidComum>> bando;

        GLfloat inicio;
        GLfloat fim;
        GLfloat dir;
        GLfloat esq;

        double fatCentro;
        double fatCurva;
        double fatVelLoc;
        double fatSeparar;
        double campoVisao;
        


        Vector3 voarParaCentro(Boid& b);
        Vector3 manterDistanciaOutros(Boid& b);
        Vector3 velocidadesSimilares(Boid& b);
        Vector3 manterLimites(Boid& b);
};

#endif

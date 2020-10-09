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
        void removeBoid();
        void addSeparacao(double delta);
        void addVelLocal(double delta);
        void addCampoVisao(double delta);

        Vector3 getLiderPos();
        Vector3 getLiderVel();
        Vector3 getLiderNor();

        void liderYawEsq();
        void liderYawDir();
    private:
        Vector3 centroBando;

        std::shared_ptr<BoidLider> lider;
        std::vector<std::shared_ptr<BoidComum>> bando;

        double fatCentro;
        double fatCurva;
        double fatVelLoc;
        double fatSeparar;
        double fatLider;
        double campoVisao;
        
        Vector3 voarParaCentro(Boid& b);
        Vector3 manterDistanciaOutros(Boid& b);
        Vector3 velocidadesSimilares(Boid& b);
        Vector3 manterLimites(Boid& b);
        Vector3 seguirLider(Boid& b);
};

#endif

#ifndef BANDO_H
#define BANDO_H

#include <memory>
#include <vector>
#include "gObject.h"
#include "obstaculos.h"
#include "boidLider.h"
#include "boidComum.h"

class Bando : public GameObject{
    public:
        Bando(Vector3 _posleader);
        void draw();
        void update();

        void addBoid();
        void removeBoid();
        Vector3 getCentroBando();
        void toggleDebug();
        void addSeparacao(double delta);
        void addVelLocal(double delta);
        void addCampoVisao(double delta);
        void addObstaculo(std::shared_ptr<Obstaculo> obs);

        Vector3 getLiderPos();
        Vector3 getLiderVel();
        Vector3 getLiderNor();

        void liderYawEsq();
        void liderYawDir();
        void liderPitchUp();
        void liderPitchDown();
        void liderRollEsq();
        void liderRollDir();
    private:
        Vector3 centroBando;

        std::shared_ptr<BoidLider> lider;
        std::vector<std::shared_ptr<BoidComum>> bando;
        std::vector<std::shared_ptr<Obstaculo>> obstaculos;

        double fatCentro;
        double fatCurva;
        double fatVelLoc;
        double fatSeparar;
        double fatLider;
        double campoVisao;

        bool debugEnabled;
        
        Vector3 voarParaCentro(Boid& b);
        Vector3 manterDistanciaOutros(Boid& b);
        Vector3 velocidadesSimilares(Boid& b);
        Vector3 manterLimites(Boid& b);
        Vector3 tenderPara(Boid& b, Vector3 liderPos);
};

#endif

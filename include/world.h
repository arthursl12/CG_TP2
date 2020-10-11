/**
 * Classe World.
 *
 * Gerencia todos os objetos e sua existência na cena
 *
 * @param 
 *      
 */

#ifndef WORLD_H
#define WORLD_H

#include "constants.h"
#include "bando.h"
#include "torre.h"
#include "obstaculos.h"


class World{
    public:
        World();
        World(const World& old);
        void draw();
        void update();
        void view();

        void moveObservador(int frente, int direita, int cima);
        void changeCamera(Camera newC);

        void toggleFog();
        void reset();

        void addBoid();
        void removeBoid();

        void addSeparacao(double delta);
        void addVelLocal(double delta);
        void addCampoVisao(double delta);

        void liderYawEsq();
        void liderYawDir();
        void liderPitchUp();
        void liderPitchDown();
    private:
        Vector3 observador;
        double zoomFactor;
        Vector3 alvo;
        Vector3 normalObsvd;
        Camera cameraAtual;
        
        std::shared_ptr<Bando> bando;
        std::vector<std::shared_ptr<Obstaculo>> obstaculos;
        bool fogEnabled;
        

        void drawGeradores();
        void drawChao();
        void drawParedes();
        void drawCeu();
};

#endif /* WORLD_H */
#ifndef TORRE_H
#define TORRE_H

#include "obstaculos.h"

class Torre : public Obstaculo {
    public:
        Torre(Vector3 _pos, double _height, double _radius);
        void draw();
        void update();
        bool proximo(Vector3 ponto);
        Vector3 maisProximo(Vector3 ponto);
    protected:
        double cylH;
        double conH;
        double totalHeight;
        double radius;
        double conRad;
};

#endif /* TORRE_H */
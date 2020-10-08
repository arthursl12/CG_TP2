#ifndef TORRE_H
#define TORRE_H

#include "gObject.h"

class Torre : public GameObject {
    public:
        Torre(Vector3 _pos, double _height, double _radius);
        void draw();
        void update();
    protected:
        double radius;
};

#endif /* TORRE_H */
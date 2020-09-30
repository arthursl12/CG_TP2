#include "constants.h"
#include "piramide.h"
#include "boid.h"


Boid::Boid(Vector3 _pos){
    pos = _pos;
    velocity = Vector3(0,1,-0.2);
}

void Boid::update(){
    double passo = BOID_PASSO;
    if (DBG) passo = passo/5;
    pos += velocity * passo;
}

BoidComum::BoidComum(Vector3 _pos) : 
    Boid(_pos)
{
}

void BoidComum::draw(){
    // Asa direita
    glColor3f(1,1,0.2);
    Vector3 p1(pos.X, pos.Y, pos.Z + 2);
    Vector3 v1(0,0,20);
    Piramide pir1(p1, v1, 0, -15, 0, 15, 15);
    pir1.draw();

    // Asa esquerda
    glColor3f(1,1,0.2);
    Vector3 p2(pos.X, pos.Y, pos.Z - 2);
    Vector3 v2(0,0,-20);
    Piramide pir2(p2, v2, 0, 15, 0, 15, 15);
    pir2.draw();

    // Cauda
    glColor3f(0.7,0.7,0);
    Vector3 p3(pos.X - 17, pos.Y, pos.Z);
    Vector3 v3(0,0,10);
    Piramide pir3(p3, v3, 0, 90, 0, 10, 10);
    pir3.draw();

    // Corpo
    glColor3f(0.7,0.7,0);
    Vector3 p5(pos.X + 7, pos.Y, pos.Z);
    Vector3 v5(0,7.6,-14);
    Piramide pir5(p5, v5, 0, 90, 0, 8, 15);
    pir5.draw();

    // Cabeça
    glColor3f(1,0.2,0);
    Vector3 p4(pos.X + 7, pos.Y, pos.Z);
    Vector3 v4(0,0,10);
    Piramide pir4(p4, v4, 0, 90, 0, 8, 15);
    pir4.draw();
}


BoidLider::BoidLider(Vector3 _pos) : 
    Boid(_pos)
{
}

void BoidLider::draw(){
    // Asa direita
    glColor3f(1,0.5,0);
    Vector3 p1(pos.X, pos.Y, pos.Z + 2);
    Vector3 v1(0,0,20);
    Piramide pir1(p1, v1, 0, -15, 0, 15, 15);
    pir1.draw();

    // Asa esquerda
    glColor3f(1,0.5,0);
    Vector3 p2(pos.X, pos.Y, pos.Z - 2);
    Vector3 v2(0,0,-20);
    Piramide pir2(p2, v2, 0, 15, 0, 15, 15);
    pir2.draw();

    // Cauda
    glColor3f(0.4,0.4,0);
    Vector3 p3(pos.X - 17, pos.Y, pos.Z);
    Vector3 v3(0,0,10);
    Piramide pir3(p3, v3, 0, 90, 0, 10, 10);
    pir3.draw();

    // Corpo
    glColor3f(0.4,0.4,0);
    Vector3 p5(pos.X + 7, pos.Y, pos.Z);
    Vector3 v5(0,7.6,-14);
    Piramide pir5(p5, v5, 0, 90, 0, 8, 15);
    pir5.draw();

    // Cabeça
    glColor3f(1,0,0);
    Vector3 p4(pos.X + 7, pos.Y, pos.Z);
    Vector3 v4(0,0,10);
    Piramide pir4(p4, v4, 0, 90, 0, 8, 15);
    pir4.draw();


}

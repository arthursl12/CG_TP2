#include "utils.h"
#include "piramide.h"
#include "boidComum.h"

BoidComum::BoidComum(Vector3 _pos) : 
    Boid(_pos)
{
    totalRotation = Quaternion::Identity();
}

void BoidComum::addVelocity(Vector3 deltaV){
    Vector3 oldV = velocity;
    velocity = velocity + deltaV;
    if (Vector3::Magnitude(velocity) >= BOID_MAX_VEL){
        velocity = (velocity/Vector3::Magnitude(velocity)) * BOID_MAX_VEL;
    }


    Quaternion q0 = Quaternion::FromToRotation(oldV, velocity);
    Vector3 cimaAtual = mulQuatVec(q0,cima);
    if (cimaAtual.Y < 0){
        cimaAtual.Y = -cimaAtual.Y;
    }
    Quaternion q1 = Quaternion::FromToRotation(cima, cimaAtual);
    totalRotation = q0 * totalRotation;
}

void BoidComum::fugir(Vector3 newV){
    Vector3 oldV = velocity;
    velocity = newV;
    if (Vector3::Magnitude(velocity) >= BOID_MAX_VEL){
        velocity = (velocity/Vector3::Magnitude(velocity)) * BOID_MAX_VEL;
    }


    Quaternion q0 = Quaternion::FromToRotation(oldV, velocity);
    Vector3 cimaAtual = mulQuatVec(q0,cima);
    if (cimaAtual.Y < 0){
        cimaAtual.Y = -cimaAtual.Y;
    }
    Quaternion q1 = Quaternion::FromToRotation(cima, cimaAtual);
    totalRotation = q0 * totalRotation;
}

void BoidComum::draw(){
    glPushMatrix();

    totalRotation = Quaternion::Normalized(totalRotation);
    Quaternion q = Quaternion::RotateTowards(Quaternion::Identity(),totalRotation,M_PI)/20;
    Matrix3x3 m1 = Matrix3x3::FromQuaternion(q);

    frente = mulQuatVec(q, frente);
    cima = mulQuatVec(q,cima);
    esq = mulQuatVec(q, esq);

    glTranslatef(pos.X,pos.Y,pos.Z);
    glMultMatrixd(expande(m1));
    glTranslatef(-pos.X,-pos.Y,-pos.Z);

    double pontaAsa = flapTimer/WING_FLAP_PROP - WING_FLAP_PROP/2;
    // Asa direita
    glColor3f(1,1,0.2);
    Vector3 p1(pos.X, pos.Y, pos.Z + 2);
    Vector3 v1(0,pontaAsa,20);
    Piramide pir1(p1, v1, 0, -15, 0, 15, 15);
    pir1.draw();

    // Asa esquerda
    glColor3f(1,1,0.2);
    Vector3 p2(pos.X, pos.Y, pos.Z - 2);
    Vector3 v2(0,pontaAsa,-20);
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

    glPopMatrix();
}
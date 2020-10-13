#include "utils.h"
#include "piramide.h"
#include "boidLider.h"


BoidLider::BoidLider(Vector3 _pos) : 
    Boid(_pos)
{
    totalRotation = Quaternion::Identity();
}

void BoidLider::atualizaEixos(Quaternion q){
    velocity = mulQuatVec(q, velocity);
    cima = mulQuatVec(q, cima);
    esq = mulQuatVec(q, esq);
    totalRotation = q * totalRotation;
}

void BoidLider::update(){
    pos += velocity * BOID_PASSO;
    flapTimer += 1;

    if (flapTimer >= WING_FLAP_INTERVAL){
        flapTimer = 0;
    }
    if (Vector3::Magnitude(velocity) <= BOID_MAX_VEL/1.3){
        velocity *= 1.05;
    }

    if (pos.Y <= LIDER_MIN_Y){
        pos.Y = LIDER_MIN_Y;
    }
}

void BoidLider::yawEsq(){
    Quaternion q = Quaternion::FromAngleAxis(YAW_ANGLE,cima);
    atualizaEixos(q);
}
void BoidLider::yawDir(){
    Quaternion q = Quaternion::FromAngleAxis(-YAW_ANGLE,cima);
    atualizaEixos(q);
}
void BoidLider::pitchUp(){
    Quaternion q = Quaternion::FromAngleAxis(-PITCH_ANGLE,esq);
    atualizaEixos(q);
}
void BoidLider::pitchDown(){
    Quaternion q = Quaternion::FromAngleAxis(PITCH_ANGLE,esq);
    atualizaEixos(q);
}

void BoidLider::draw(){
    glPushMatrix();
    totalRotation = Quaternion::Normalized(totalRotation);
    Quaternion q = totalRotation;
    Matrix3x3 m1 = Matrix3x3::FromQuaternion(q);

    glTranslatef(pos.X,pos.Y,pos.Z);
    glMultMatrixd(expande(m1));
    glTranslatef(-pos.X,-pos.Y,-pos.Z);
    
    double pontaAsa = flapTimer/WING_FLAP_PROP - WING_FLAP_PROP/2;
    // Asa direita
    glColor3f(1,0.5,0);
    Vector3 p1(pos.X, pos.Y, pos.Z + 2);
    Vector3 v1(0,pontaAsa,20);
    Piramide pir1(p1, v1, 0, -15, 0, 15, 15);
    pir1.draw();

    // Asa esquerda
    glColor3f(1,0.5,0);
    Vector3 p2(pos.X, pos.Y, pos.Z - 2);
    Vector3 v2(0,pontaAsa,-20);
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
    glPopMatrix();
}

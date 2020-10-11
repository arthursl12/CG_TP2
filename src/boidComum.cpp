#include "utils.h"
#include "piramide.h"
#include "boidComum.h"

BoidComum::BoidComum(Vector3 _pos) : 
    Boid(_pos)
{
}

void BoidComum::draw(){
    glPushMatrix();

    Quaternion q = Quaternion::FromToRotation(Vector3(1,0,0), velocity);
    Vector3 matching = Vector3::Normalized(frente) - Vector3::Normalized(velocity);
    if ( Vector3::Magnitude(matching) > 0.01 ){
        // std::cout << "Quat:" << q.W << ", " << q.X << "," << q.Y << "," << q.Z << std::endl;
        Quaternion K = Quaternion(Vector3(1,0,0),0);
        Quaternion resp = q * K * Quaternion::Conjugate(q);
        // Quaternion resp = Quaternion::RotateTowards(Quaternion())
        frente = Vector3(resp.X, resp.Y, resp.Z);

        K = Quaternion(Vector3(0,1,0),0);
        resp = q * K * Quaternion::Conjugate(q);
        cima = Vector3(resp.X, resp.Y, resp.Z);

        K = Quaternion(Vector3(0,0,-1),0);
        resp = q * K * Quaternion::Conjugate(q);
        esq = Vector3(resp.X, resp.Y, resp.Z);
    }
    Matrix3x3 m1 = Matrix3x3::FromQuaternion(q);
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
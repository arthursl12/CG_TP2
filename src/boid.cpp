#include "Quaternion.hpp"
#include "constants.h"
#include "utils.h"
#include "piramide.h"
#include "boid.h"


Boid::Boid(Vector3 _pos){
    pos = _pos;
    velocity = Vector3(1,0,0);      // Direção que o boid está olhando inicialmente
    frente = Vector3(1,0,0);
    oldV = Vector3(1,0,0);

    cima = Vector3(0,1,0);
    esq = Vector3(0,0,-1);
    // Quaternion qy = Quaternion::FromAngleAxis(+M_PI/3,Vector3(0,1,0));
    // Quaternion q = qy;
    // Quaternion K = Quaternion(velocity,0);
    // Quaternion resp = q * K * Quaternion::Conjugate(q);
    // velocity = Vector3(resp.X, resp.Y, resp.Z);

    flapTimer = 0;
}

void Boid::update(){
    double passo = BOID_PASSO;
    if (DBG) passo = passo;
    pos += velocity * passo;
    flapTimer += 1;

    if (flapTimer >= WING_FLAP_INTERVAL){
        flapTimer = 0;
    }



}

void BoidLider::yawEsq(){
    Quaternion K = Quaternion(velocity,0);
    Quaternion q = Quaternion::FromAngleAxis(M_PI/6,cima);
    Quaternion resp = q * K * Quaternion::Conjugate(q);
    // Quaternion resp = Quaternion::RotateTowards(Quaternion())
    velocity = Vector3(resp.X, resp.Y, resp.Z);

    K = Quaternion(cima,0);
    resp = q * K * Quaternion::Conjugate(q);
    cima = Vector3(resp.X, resp.Y, resp.Z);

    K = Quaternion(esq,0);
    resp = q * K * Quaternion::Conjugate(q);
    esq = Vector3(resp.X, resp.Y, resp.Z);

    totalRotation = q * totalRotation;
    // K = Quaternion(frente,0);
    // resp = q * K * Quaternion::Conjugate(q);
    // frente = Vector3(resp.X, resp.Y, resp.Z);
    // addVelocity(0.1 * esq);
    // velocity += 0.1 * esq;
}

void BoidLider::yawDir(){
    Quaternion K = Quaternion(velocity,0);
    Quaternion q = Quaternion::FromAngleAxis(-M_PI/6,cima);
    Quaternion resp = q * K * Quaternion::Conjugate(q);
    // Quaternion resp = Quaternion::RotateTowards(Quaternion())
    velocity = Vector3(resp.X, resp.Y, resp.Z);

    K = Quaternion(cima,0);
    resp = q * K * Quaternion::Conjugate(q);
    cima = Vector3(resp.X, resp.Y, resp.Z);

    K = Quaternion(esq,0);
    resp = q * K * Quaternion::Conjugate(q);
    esq = Vector3(resp.X, resp.Y, resp.Z);

    totalRotation = q * totalRotation;
    // K = Quaternion(frente,0);
    // resp = q * K * Quaternion::Conjugate(q);
    // frente = Vector3(resp.X, resp.Y, resp.Z);
    // addVelocity(-0.1 * esq);
    // velocity -= 0.1 * esq;
}

void BoidLider::pitchUp(){
    // Vector3 cimaNorm = Vector3::Normalized(cima);

    // Vector3 direita = Vector3::Cross(frente,cimaNorm);
    // Vector3 dirNorm = Vector3::Normalized(direita);

    // Vector3 trasNorm = Vector3::Cross(dirNorm, cimaNorm);
    Quaternion K = Quaternion(velocity,0);
    Quaternion q = Quaternion::FromAngleAxis(-M_PI/20,esq);
    Quaternion resp = q * K * Quaternion::Conjugate(q);
    velocity = Vector3(resp.X, resp.Y, resp.Z);

    K = Quaternion(cima,0);
    resp = q * K * Quaternion::Conjugate(q);
    cima = Vector3(resp.X, resp.Y, resp.Z);

    K = Quaternion(esq,0);
    resp = q * K * Quaternion::Conjugate(q);
    esq = Vector3(resp.X, resp.Y, resp.Z);

    totalRotation = q * totalRotation;

    // K = Quaternion(frente,0);
    // resp = q * K * Quaternion::Conjugate(q);
    // frente = Vector3(resp.X, resp.Y, resp.Z);
    // addVelocity(0.1 * cima);
    // velocity += 0.1 * cima;
    // cima += 1 * trasNorm;
}
void BoidLider::pitchDown(){
    // Quaternion K = Quaternion(velocity,0);
    // Quaternion q = Quaternion::FromAngleAxis(M_PI/20,esq);
    // Quaternion resp = q * K * Quaternion::Conjugate(q);
    // velocity = Vector3(resp.X, resp.Y, resp.Z);

    // K = Quaternion(cima,0);
    // resp = q * K * Quaternion::Conjugate(q);
    // cima = Vector3(resp.X, resp.Y, resp.Z);
    Quaternion K = Quaternion(velocity,0);
    Quaternion q = Quaternion::FromAngleAxis(M_PI/20,esq);
    Quaternion resp = q * K * Quaternion::Conjugate(q);
    velocity = Vector3(resp.X, resp.Y, resp.Z);

    K = Quaternion(cima,0);
    resp = q * K * Quaternion::Conjugate(q);
    cima = Vector3(resp.X, resp.Y, resp.Z);

    K = Quaternion(esq,0);
    resp = q * K * Quaternion::Conjugate(q);
    esq = Vector3(resp.X, resp.Y, resp.Z);

    totalRotation = q * totalRotation;
    // K = Quaternion(frente,0);
    // resp = q * K * Quaternion::Conjugate(q);
    // frente = Vector3(resp.X, resp.Y, resp.Z);
    // velocity -= 0.1 * cima;
}

bool Boid::operator!=(Boid& outro){
    Vector3 vecDist = this->pos - outro.pos;
    double dist = Vector3::Magnitude(vecDist);

    if (dist >= 1){
        return true;
    }else{
        return false;
    }
}

void Boid::addVelocity(Vector3 deltaV){
    
    // frente = frente + deltaV;
    oldV = velocity;
    velocity = velocity + deltaV;
    // velocity += deltaV;
    if (Vector3::Magnitude(velocity) >= BOID_MAX_VEL){
        velocity = (velocity/Vector3::Magnitude(velocity)) * BOID_MAX_VEL;
    }
    // Quaternion target = Quaternion::FromToRotation(oldV, velocity);
    // // std::cout << "Target:" << target.W << ", " << target.X << "," << target.Y << "," << target.Z << std::endl;
    // float matching = Quaternion::Dot(target, pose);
    // oldPose = pose;
    // if ( abs(matching - 1.0) > 0.001 ){
    //     pose = target * pose;
    // }
    // if (pose != Quaternion::Identity()){
    //     std::cout << "Pose:" << pose.W << ", " << pose.X << "," << pose.Y << "," << pose.Z << std::endl;
    // }
    // std::cout << "V: " << velocity.X << "," << velocity.Y << "," << velocity.Z << std::endl;
    // std::cout << "O: " << oldV.X << "," << oldV.Y << "," << oldV.Z << std::endl;


    // std::cout << "Q1: " << q.X << "," << q.Y << "," << q.Z << std::endl;
    // std::cout << "O1: " << oldV.X << "," << oldV.Y << "," << oldV.Z << std::endl;
}

BoidComum::BoidComum(Vector3 _pos) : 
    Boid(_pos)
{
}

void BoidComum::draw(){
    glPushMatrix();
    // "Olhar" para a nova velocidade
    // float matching = Quaternion::Dot(oldPose, pose);
    // if ( abs(matching - 1.0) > 0.001 ){
    //     Matrix3x3 m1 = Matrix3x3::FromQuaternion(pose);
    //     glMultMatrixd(expande(m1));
    //     std::cout << "AUI" << std::endl;
    // }
    
    // Quaternion qx = Quaternion::FromAngleAxis(0,Vector3(1,0,0));

    // Quaternion qy = Quaternion::FromAngleAxis(M_PI/4,Vector3(0,-1,0));
    // Quaternion qz = Quaternion::FromAngleAxis(M_PI/3,Vector3(0,0,1));
    // Quaternion q = qy * qz;
    
    // "Virei" a frente do Boid e a sua velocidade

    // velocity = Vector3(resp.X, resp.Y, resp.Z);

    
    // std::cout << "Fr:" << frente.X << "," << frente.Y << "," << frente.Z << std::endl;
    // std::cout << "Ve:" << velocity.X << "," << velocity.Y << "," << velocity.Z << std::endl;
    // std::cout << "Ma:" << matching.X << "," << matching.Y << "," << matching.Z << std::endl;
    // std::cout << Vector3::Magnitude(matching) << std::endl;
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
    // std::cout << "PA: " << pontaAsa << std::endl;
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


BoidLider::BoidLider(Vector3 _pos) : 
    Boid(_pos)
{
    normal = Vector3(0,1,0);
    totalRotation = Quaternion::Identity();
}

void BoidLider::draw(){
    glPushMatrix();
    Quaternion qF = Quaternion::FromToRotation(Vector3(1,0,0),  velocity);
    // Quaternion qN = Quaternion::FromToRotation(Vector3(0,1,0),  cima);
    // Quaternion qE = Quaternion::FromToRotation(Vector3(0,0,-1), esq);

    // Quaternion q = qF * qN * qE;
    // Quaternion q = qF * qE * qN; //Esse
    // Quaternion q = qN * qF * qE;
    // Quaternion q = qN * qE * qF;
    // Quaternion q = qE * qF * qN;
    // Quaternion q = qE * qN * qF;
    totalRotation = Quaternion::Normalized(totalRotation);
    Quaternion q = totalRotation; //Esse
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

#include "boid.h"

#include "piramide.h"

Boid::Boid(vec3 _pos){
    pos = _pos;
}

void Boid::draw(){
    // Asa direita
    glColor3f(1,1,0.2);
    vec3 p1(pos.x, pos.y, pos.z + 2);
    vec3 v1(0,0,20);
    Piramide pir1(p1, v1, 0, -15, 0, 15, 15);
    pir1.draw();

    // Asa esquerda
    glColor3f(1,1,0.2);
    vec3 p2(pos.x, pos.y, pos.z - 2);
    vec3 v2(0,0,-20);
    Piramide pir2(p2, v2, 0, 15, 0, 15, 15);
    pir2.draw();

    // Cauda
    glColor3f(0.7,0.7,0);
    vec3 p3(pos.x - 17, pos.y, pos.z);
    vec3 v3(0,0,10);
    Piramide pir3(p3, v3, 0, 90, 0, 10, 10);
    pir3.draw();

    // Corpo
    glColor3f(0.7,0.7,0);
    vec3 p5(pos.x + 7, pos.y, pos.z);
    vec3 v5(0,7.6,-14);
    Piramide pir5(p5, v5, 0, 90, 0, 8, 15);
    pir5.draw();

    // Cabeça
    glColor3f(1,0.2,0);
    vec3 p4(pos.x + 7, pos.y, pos.z);
    vec3 v4(0,0,10);
    Piramide pir4(p4, v4, 0, 90, 0, 8, 15);
    pir4.draw();


}

void Boid::update(){

}
#include "linalg.h"
#include <cmath>
#include <iostream>

vec3 vec3::operator+(const vec3& vec){
    GLfloat newX = this->x + vec.x;
    GLfloat newY = this->y + vec.y;
    GLfloat newZ = this->z + vec.z;
    return vec3(newX, newY, newZ);
}

vec3 vec3::operator+=(const vec3& vec){
    x += vec.x;
    y += vec.y;
    z += vec.z;
    return *this;
}

vec3 vec3::operator-(const vec3& vec){
    GLfloat newX = this->x - vec.x;
    GLfloat newY = this->y - vec.y;
    GLfloat newZ = this->z - vec.z;
    return vec3(newX, newY, newZ);
}

vec3 vec3::operator-=(const vec3& vec){
    x -= vec.x;
    y -= vec.y;
    z -= vec.z;
    return *this;
}



void vec3::normalizar(){
    GLfloat norma = sqrt(pow(x,2) + pow(y,2) + pow(z,2));
    x = x/norma;
    y = y/norma;
    z = z/norma;
}

std::ostream& operator<<(std::ostream &out, const vec3& vec){
    out << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
    return out;
}
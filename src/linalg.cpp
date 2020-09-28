#include "linalg.h"
#include <cmath>
#include <iostream>

vec3::vec3(){
    x = 0;
    y = 0;
    z = 0;
}
vec3::vec3(const vec3& old){
    x = old.x;
    y = old.y;
    z = old.z;
}

vec3& vec3::operator= (const vec3& vec){
    x = vec.x;
    y = vec.y;
    z = vec.z;
    return *this;
}

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

vec3 vec3::operator-(){
    vec3 newVec = vec3(-x, -y, -z);
    return newVec;
}

vec3 vec3::operator-=(const vec3& vec){
    x -= vec.x;
    y -= vec.y;
    z -= vec.z;
    return *this;
}

void vec3::normalizar(){
    x = x/norma();
    y = y/norma();
    z = z/norma();
}

GLfloat vec3::norma(){
    return sqrt(pow(x,2) + pow(y,2) + pow(z,2));
}


std::ostream& operator<<(std::ostream &out, const vec3& vec){
    out << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
    return out;
}

vec3 vec3::operator*(const vec3& vec){
    GLfloat p1 = (y * vec.z) - (vec.y * z);
    GLfloat p2 = (x * vec.z) - (vec.x * z);
    GLfloat p3 = (x * vec.y) - (vec.x * y);
    return vec3(p1, -p2, p3);
}

vec3 vec3::operator*(const GLfloat escalar){
    x *= escalar;
    y *= escalar;
    z *= escalar;
    return *this;
}
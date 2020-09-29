/**
 * Biblioteca de Álgebra Linear.
 *
 * Utiliza uma classe vec3 para representar um vetor tridimensional e suas
 * operações básicas
 *
 * @param (vec3)
 *      _x  : coordenada x do vetor
 *      _y  : coordenada y do vetor
 *      _z  : coordenada z do vetor
 * 
 */
#ifndef LINALG_H
#define LINALG_H

#include "GL/gl.h"
#include <ostream>

class vec3{
    public:
        GLfloat x;
        GLfloat y;
        GLfloat z;
        vec3(GLfloat _x, GLfloat _y, GLfloat _z){
            x = _x;
            y = _y;
            z = _z;
        }
        vec3();
        vec3(const vec3& old);
        void normalizar();
        GLfloat norma();

        friend std::ostream& operator<<(std::ostream &out, const vec3& vec);
        vec3& operator= (const vec3& vec);
        vec3 operator+(const vec3& vec);
        vec3 operator+=(const vec3& vec);
        vec3 operator-(const vec3& vec);
        vec3 operator-();
        vec3 operator-=(const vec3& vec);
        vec3 operator*(const vec3& vec);
        vec3 operator*(const GLfloat escalar);

};

#endif
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

        friend std::ostream& operator<<(std::ostream &out, const vec3& vec);
        vec3& operator= (const vec3& vec);
        vec3 operator+(const vec3& vec);
        vec3 operator+=(const vec3& vec);
        vec3 operator-(const vec3& vec);
        vec3 operator-=(const vec3& vec);
        vec3 operator*(const vec3& vec);
        vec3 operator*(const GLfloat escalar);

};

#endif
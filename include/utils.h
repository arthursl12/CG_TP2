#ifndef UTILS_H
#define UTILS_H

#include <GL/gl.h>
#include <Matrix3x3.hpp>
#include <string>

#include "constants.h"

void display_callback();
void view_callback(void);
void reshape_callback(int,int);
void timer_callback(int);
void keyboard_callback(unsigned char, int, int);
void keyboard_special_callback(int key, int x, int y);
void mouse_callback(int button, int state, int x, int y);
GLdouble* expande(Matrix3x3& rot);
Vector3 mulQuatVec(Quaternion q, Vector3 vec);

#endif /* UTILS_H */
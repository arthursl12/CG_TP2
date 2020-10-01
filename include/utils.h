#ifndef UTILS_H
#define UTILS_H

#include "constants.h"
#include <GL/gl.h>
#include <string>
#include "Matrix3x3.hpp"


extern bool gameOver;
extern int score;

void drawText(float x, float y, std::string text);
void display_callback();
void EspecificaParametrosVisualizacao(void);
void reshape_callback(int,int);
void timer_callback(int);
void keyboard_callback(unsigned char, int, int);
void keyboard_special_callback(int key, int x, int y);
void motion_callback(int x, int y);
void mouse_callback(int button, int state, int x, int y);
GLdouble* expande(Matrix3x3& rot);

#endif /* UTILS_H */
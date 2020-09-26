#ifndef UTILS_H
#define UTILS_H

#include "constants.h"
#include <string>

extern bool gameOver;
extern int score;

void drawText(float x, float y, std::string text);
void display_callback();
void EspecificaParametrosVisualizacao(void);
void reshape_callback(int,int);
void timer_callback(int);
void keyboard_callback(unsigned char, int, int);
void motion_callback(int x, int y);
void mouse_callback(int button, int state, int x, int y);

#endif /* UTILS_H */
#include "GL/gl.h"
#include "GL/glut.h"
#include <iostream>
#include <memory>
#include <ctime>
#include <cstdlib>

#include "world.h"
#include "constants.h"
#include "utils.h"

World world;
GLfloat angle, fAspect;

/**
 * Parâmetros da Iluminação
 * 
 * Adaptado de: https://www.inf.pucrs.br/~manssour/OpenGL/Iluminacao.html
**/
void initIluminacao(){
	GLfloat luzAmbiente[4]={0.2,0.2,0.2,1.0}; 
	GLfloat luzDifusa[4]={0.7,0.7,0.7,1.0};	        // "cor" 
	GLfloat luzEspecular[4]={1.0, 1.0, 1.0, 1.0};   // "brilho" 
	GLfloat posicaoLuz[4]={0.0, 50.0, 50.0, 1.0};

	// Capacidade de brilho do material
	GLfloat especularidade[4]={1.0,1.0,1.0,1.0}; 
	GLint especMaterial = 60;

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	
	glShadeModel(GL_SMOOTH);
	glMaterialfv(GL_FRONT,GL_SPECULAR, especularidade);
	glMateriali(GL_FRONT,GL_SHININESS,especMaterial);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

	// Define os parâmetros da luz de número 0
	glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente); 
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa );
	glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular );
	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz );

	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);  
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
}

/**
 * Parâmetros da Fog (névoa), inicialmente desligada
 * 
 * Adaptado de: https://www.dca.ufrn.br/~lmarcos/courses/compgraf/redbook/chapter06.html
**/
void initFog(){
	GLfloat fogColor[4] = {0.5, 0.5, 0.5, 1.0};
	glFogi(GL_FOG_MODE, GL_LINEAR);
	glFogfv(GL_FOG_COLOR, fogColor);
	glFogf(GL_FOG_DENSITY, 0.35);
	glHint(GL_FOG_HINT, GL_DONT_CARE);
	glFogf(GL_FOG_START, 1.0);
	glFogf(GL_FOG_END, 3000);
}

void init(){
	angle = 45; 	// FOV inicial
	initIluminacao();
	initFog();
}

int main(int argc, char **argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(WINDOW_W, WINDOW_H);

	glutCreateWindow("Boids - OpenGL");
	glutDisplayFunc(display_callback);
	glutReshapeFunc(reshape_callback);
	glutTimerFunc(0, timer_callback, 0);
	glutKeyboardFunc(keyboard_callback);
    glutSpecialFunc(keyboard_special_callback);
	glutMouseFunc(mouse_callback);

	init();
	glutMainLoop();
	return 0;

}




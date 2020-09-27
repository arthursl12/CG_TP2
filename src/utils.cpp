#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <iostream>
#include <string>
#include <vector>
#include <iterator>

#include "gObject.h"
#include "world.h"
#include "utils.h"

extern World world;
extern GLfloat angle, fAspect;

void drawText(float x, float y, std::string text) {
    glRasterPos2f(x, y);
    glutBitmapString(GLUT_BITMAP_8_BY_13, (const unsigned char*)text.c_str());
}

void display_callback(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(0.0f, 0.0f, 1.0f);

	// Desenha o teapot com a cor corrente (wire-frame)
	world.draw();

	// lev.draw();
	// lev.update();
	glutSwapBuffers();
}

void keyboard_callback(unsigned char key, int, int){
	switch(key){
		case 'q':
			exit(0);
			break;
		case 'r':{
			// lev = Level(lev);
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f );
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glutPostRedisplay();
			break;
		}
		case 'p':{
			// if (DBG){
			// 	lev.debugComplete();
			// }
		}
	}
}

void keyboard_special_callback(int key, int x, int y){
    switch (key){
    case GLUT_KEY_UP:
		// std::cout << "UP" << std::endl;
        world.moveObservador(1, 0, 0);
        EspecificaParametrosVisualizacao();
		glutPostRedisplay();
        break;
	case GLUT_KEY_DOWN:
		// std::cout << "UP" << std::endl;
        world.moveObservador(-1, 0, 0);
        EspecificaParametrosVisualizacao();
		glutPostRedisplay();
        break;
    default:
        break;
    }
}

void motion_callback(int x, int y){
	// lev.setMousePos(x, y);
}

void timer_callback(int){
	// if (!lev.getIsPaused()){
	// 	glClearColor(0.0f, 0.0f, 0.0f, 1.0f );
	// 	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// 	glutPostRedisplay();
	// }

	glutTimerFunc(1000/FPS,timer_callback,0);
}

// Função usada para especificar o volume de visualização
void EspecificaParametrosVisualizacao(void)
{
	// Especifica sistema de coordenadas de projeção
	glMatrixMode(GL_PROJECTION);
	// Inicializa sistema de coordenadas de projeção
	glLoadIdentity();

	// Especifica a projeção perspectiva
	gluPerspective(angle,fAspect,0.1,500);

	// Especifica sistema de coordenadas do modelo
	glMatrixMode(GL_MODELVIEW);
	// Inicializa sistema de coordenadas do modelo
	glLoadIdentity();

    world.view();
}

// Função callback chamada quando o tamanho da janela é alterado 
void reshape_callback(GLsizei w, GLsizei h)
{
	// Para previnir uma divisão por zero
	if ( h == 0 ) h = 1;

	// Especifica o tamanho da viewport
	glViewport(0, 0, w, h);
 
	// Calcula a correção de aspecto
	fAspect = (GLfloat)w/(GLfloat)h;

	EspecificaParametrosVisualizacao();
}

// Função callback chamada para gerenciar eventos do mouse
void mouse_callback(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
		if (state == GLUT_DOWN) {  // Zoom-in
			if (angle >= 10) angle -= 5;
		}
	if (button == GLUT_RIGHT_BUTTON)
		if (state == GLUT_DOWN) {  // Zoom-out
			if (angle <= 130) angle += 5;
		}
	EspecificaParametrosVisualizacao();
	glutPostRedisplay();
}
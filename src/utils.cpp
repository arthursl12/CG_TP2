#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <iostream>
#include <string>
#include <vector>
#include <iterator>

#include "constants.h"
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
    glClearDepth(10.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(0.0f, 0.0f, 1.0f);

	// Desenha o teapot com a cor corrente (wire-frame)
	world.draw();
	world.update();

	// lev.draw();
	// lev.update();
	
	glutSwapBuffers();
	EspecificaParametrosVisualizacao();
	glutPostRedisplay();
	
}

void keyboard_callback(unsigned char key, int, int){
	// Controles líder
	switch(key){
		case 'q':
			world.liderYawEsq();
			break;
		case 'e':
			world.liderYawDir();
			break;
		case 'w':
			world.liderPitchUp();
			break;
		case 's':
			world.liderPitchDown();
			break;
	}

	// Outros controles
	switch (key){
		case '1':{
			world.changeCamera(AltoTorre);
			break;
		}
		case '2':{
			world.changeCamera(Chase);
			break;
		}
		case '3':{
			world.changeCamera(ChaseLateral);
			break;
		}
		case 'f':{
			world.toggleFog();
			break;
		}
		case 'r':{
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f );
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			world.reset();
			EspecificaParametrosVisualizacao();
			glutPostRedisplay();
			break;
		}
	}

	// Quantidade de Boids
	switch (key){
		case '+':{
			world.addBoid();
			break;
		}
		case '=':{
			// Esse é o mais ao lado do backspace
			world.addBoid();
			break;
		}
		case '-':{
			world.removeBoid();
			break;
		}
	}

	// Mudança em fatores
	switch (key){
		// Altera fator de curva
		case 't':{
			world.addCampoVisao(+20);
			break;
		}
		case 'g':{
			world.addCampoVisao(-20);
			break;
		}

		// Altera o campo de visão
		case 'y':{
			world.addVelLocal(+FATOR_VEL_LOCAL_DELTA);
			break;
		}
		case 'h':{
			world.addVelLocal(-FATOR_VEL_LOCAL_DELTA);
			break;
		}

		// Altera fator de separação
		case 'u':{
			world.addSeparacao(+FATOR_SEPARACAO_DELTA);
			break;
		}
		case 'j':{
			world.addSeparacao(-FATOR_SEPARACAO_DELTA);
			break;
		}
	}
}

void keyboard_special_callback(int key, int x, int y){
    switch (key){
    case GLUT_KEY_UP:
        world.moveObservador( 1, 0, 0);
        world.view();
		glutPostRedisplay();
        break;
	case GLUT_KEY_DOWN:
        world.moveObservador(-1, 0, 0);
        world.view();
		glutPostRedisplay();
        break;
	case GLUT_KEY_RIGHT:
		world.moveObservador( 0, 1, 0);
        world.view();
		glutPostRedisplay();
		break;
	case GLUT_KEY_LEFT:
		world.moveObservador( 0,-1, 0);
        world.view();
		glutPostRedisplay();
		break;
	case GLUT_KEY_SHIFT_R:
		world.moveObservador( 0, 0, 1);
        world.view();
		glutPostRedisplay();
		break;
	case GLUT_KEY_CTRL_R:
		world.moveObservador( 0, 0,-1);
        world.view();
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
	gluPerspective(angle,fAspect,40,DRAW_DISTANCE);

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

GLdouble* expande(Matrix3x3& rot){
    GLdouble* mat = new GLdouble [16];
    mat[0] = rot.D00;
    mat[1] = rot.D10;
    mat[2] = rot.D20;
    mat[3] = 0;

    mat[4] = rot.D01;
    mat[5] = rot.D11;
    mat[6] = rot.D21;
    mat[7] = 0;

    mat[8] = rot.D02;
    mat[9] = rot.D12;
    mat[10] = rot.D22;
    mat[11] = 0;

    mat[12] = 0;
    mat[13] = 0;
    mat[14] = 0;
    mat[15] = 1;
    return mat; 
}

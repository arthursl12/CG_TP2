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

void display_callback(){
    glClearDepth(10.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// glColor3f(0.0f, 0.0f, 1.0f);
	glColor3f(0.529, 0.808, 0.922);

	world.update();
	world.draw();

	glutSwapBuffers();
	view_callback();
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
		case 'a':
			world.liderRollEsq();
			break;
		case 'd':
			world.liderRollDir();
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

void timer_callback(int){
	glutTimerFunc(1000/FPS,timer_callback,0);
}

/**
 * Função usada para especificar o volume de visualização 
 * 
 * Adaptado de: https://www.inf.pucrs.br/~manssour/OpenGL/Programando3D.html
**/
void view_callback(void){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(angle,fAspect,40,DRAW_DISTANCE);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

    world.view();
}

/**
 * Função callback chamada quando o tamanho da janela é alterado 
 * 
 * Adaptado de: https://www.inf.pucrs.br/~manssour/OpenGL/Programando3D.html
**/
void reshape_callback(GLsizei w, GLsizei h){
	if ( h == 0 ) h = 1; 	// Evita divisão por zero
	glViewport(0, 0, w, h);
	fAspect = (GLfloat)w/(GLfloat)h;
	view_callback();
}

/**
 * Função callback chamada para gerenciar eventos do mouse
 * 
 * Adaptado de: https://www.inf.pucrs.br/~manssour/OpenGL/Programando3D.html
**/
void mouse_callback(int button, int state, int x, int y){
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		// Zoom-int
		if (angle >= 10) angle -= 5;
		
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
		// Zoom-out
		if (angle <= 90) angle += 5;
		
	view_callback();
	glutPostRedisplay();
}

/**
 * Transforma uma matriz de rotação 3x3 do tipo Matrix3x3 em uma matriz 3x3 de 
 * GLdouble, para utilização nas funções do OpenGL
**/
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

/**
 * Rotaciona um vetor segundo um quaternion fornecido
 * 
 * @param q   Quaternion de rotação
 * @param vec Vetor que será rotacionado
 * @return Novo vetor rotacionado
**/
Vector3 mulQuatVec(Quaternion q, Vector3 vec){
	Quaternion K = Quaternion(vec,0);
    Quaternion resp = q * K * Quaternion::Conjugate(q);
    return Vector3(resp.X, resp.Y, resp.Z);
}

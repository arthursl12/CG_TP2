#include "GL/gl.h"
#include "GL/glut.h"
#include <iostream>
#include <memory>
#include <ctime>
#include <cstdlib>

#include "constants.h"
#include "utils.h"

GLfloat angle, fAspect;

void init(){
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    angle=45;
}

int main(int argc, char **argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(WINDOW_W,WINDOW_H);

	glutCreateWindow("Birds - OpenGL");
	glutDisplayFunc(display_callback);
	glutReshapeFunc(reshape_callback);
	glutTimerFunc(0,timer_callback,0);
	glutKeyboardFunc(keyboard_callback);
	glutMouseFunc(mouse_callback);
	glutPassiveMotionFunc(motion_callback);
	glutMotionFunc(motion_callback);

	init();
	glutMainLoop();
	return 0;

}




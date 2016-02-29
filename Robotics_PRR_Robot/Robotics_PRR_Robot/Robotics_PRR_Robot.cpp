// Robotics_PRR_Robot.cpp : Defines the entry point for the console application.

// <stdlib.h> ALWAYS HAS TO BE INCLUDED BEFORE <GL/glut.h> OR THINGS BREAAAAAAAAAAAAK
#include <stdlib.h>
#include <GL/glut.h>

#include "Interface.h"

using namespace std;

//Interface* gui;

/*
	button = left/middle/right
	state = GLUT_UP / GLUT_DOWN
	x/y = pixels
*/
void mouseButton(int button, int state, int x, int y) {
	if (state != GLUT_UP) return;	// Only proceeds when the mouse button is released
									// Changes to the screen only happen when the mouse button is released (a button may be pressed)
	Interface::getInstance()->mouseAction = new MouseAction(x, y, button, state);
	glutPostRedisplay();	// Calls render()
							// If this was at the end of render(), the program would loop foreverrrrr
}

void render() {
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0, 0, 0, 0);	// Clears to black
	//---------------------------

	printf("-----------------New frame---------------------------(Debugging)--------\n\n");
	Interface::getInstance()->update();
	Interface::getInstance()->drawUpdate();

	//---------------------------
	glutSwapBuffers();
}

int main(int argc, char** argv) {

	Interface::getInstance(argc, argv);

	glutDisplayFunc(render);
	glutMouseFunc(mouseButton);
	glutMainLoop();

	return 1;
}


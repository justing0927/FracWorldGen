#include "GL\glew.h"
#include "GL\freeglut.h"
#include <iostream>
#include <windows.h>
#include <stdio.h>
#include "display.h"
#include "grid.h"
#include "square.h"

//bitmaps a grid object to display all the current grids characters
//Essentially displays the current world.

Grid * worldGrid;
double t; //time
int w; int h;

void updateWorldGrid(Grid * wG) {
	worldGrid = wG;
}

void setOrtho() {
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, w, 0, h);
	glScalef(1, -1, 1);
	glTranslatef(0, -h, 0);
	glMatrixMode(GL_MODELVIEW);
}

void update(int value) {
	t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
	int time = (int)t;
	//sprintf(s, "TIME : %2d Sec", time);
	glutTimerFunc(1000, update, 0);
	glutPostRedisplay();
}

void resetPerspectiveProjection() {
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}


void renderBitmapString(float x, float y, void *font, const char *string) {
	const char *c;
	glRasterPos2f(x, y);
	for (c = string; *c != '\0'; c++) {
		glutBitmapCharacter(font, *c);
	}
}


static void displayGrid(void) {
	//glMatrixMode(GL_PROJECTION);
	//glOrtho(0.0f, 1800, 1000, 0.0f, 0.0f, 1.0f);
	//glClearColor(1.0, 0.0, 0.0, 1.0); //clear red
	//std::cout << "Entering Display." << std::endl;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3d(0.0, 1.0, 0.0); //green !
	glPushMatrix();
	glLoadIdentity();
	float x = 200;
	float y = 200;
	glRasterPos2f(x, y);
	//glDisable(GL_TEXTURE_2D);
	//glColor3f(0.0, 0.0, 0.0);

	/*
	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < 9; ++j) {
			const char * c;
			std::cout << "Displaying Square: #" << ((i * 9) + j) << ", Character: " << worldGrid->getSquareAtIndex((i * 9) + j).getGraphic() << std::endl;
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, worldGrid->getSquareAtIndex((i * 9) + j).getGraphic());
			if (j == 8) {
				y += 12;
				glRasterPos2f(x, y);
			}
		}
	}
	*/
	//glEnable(GL_TEXTURE_2D);
	renderBitmapString(200, 200, GLUT_BITMAP_HELVETICA_12, "Font Rendering - Programming Techniques");
	renderBitmapString(300, 240, GLUT_BITMAP_HELVETICA_12, "Esc - Quit");
	glPopMatrix();
	resetPerspectiveProjection();
	glutSwapBuffers();
	//Sleep(5000);
}

void testDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	int x = 200;
	float y = 200;
	//glWindowPos(x, y);
	char *test = "Testing String.";
	char *c;
	for (c = test; c != "."; c++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);
	}

	glutSwapBuffers();
	Sleep(10000);
}

void resize(int width, int height) {
	const float ar = (float)width / (float)height;
	w = width;
	h = height;
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);     glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void displayWindow() {
	//unsure if necessary

	int argc = 1;
	char *argv[1] = { (char *) "Muda." };

	glutInit( &argc, argv);
	glutInitWindowPosition(10, 10); //optional
	glutInitWindowSize(640, 480); //optional
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	//glutCreateWindow("A Whole New World");
	glutCreateWindow("Font Rendering Using Bitmap Font - Programming Techniques0");
	glutReshapeFunc(resize);
	glutDisplayFunc(displayGrid);
	
	/*
	glewInit();
	if (glewIsSupported("GL_VERSION_4_5")) {
		std::cout << "GLEW Version is 4.5\n ";
	}
	else {
		std::cout << "GLEW 4.5 not supported\n ";
	}
	*/

	glutTimerFunc(25, update, 0);
	glutMainLoop();

	//glutDisplayFunc(renderScene);

	//glutMainLoop();

}

void renderScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0, 0.0, 0.0, 1.0); //clear red

	glutSwapBuffers();
}
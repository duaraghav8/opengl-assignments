/**
 * YEH BIK GAYI HAI GORMINT
 *
 * Initial line displayed has hard-coded coordinates.
 * Then user must press SPACE to clear screen and mark 2 points (mouse clicks) to draw new line.
 *
 * This is bare-minimum. This file DOES NOT PORTRAY THE DEVELOPMENT STYLE & CONVENTIONS THAT I FOLLOW IN ACTUAL
 * PRODUCTION SOFTWARE THAT I WRITE. ONLY SATAN CAN JUDGE ME ON THIS.
 *
 * COMPILATION: g++ dda.cpp -o dda -lGL -lGLU -lglut
 */

#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <cmath>
#include <iostream>

using namespace std;

struct Coord {
	double x, y;
};

struct Coord first, second;
bool firstMouseClick = false, windowCleared = true;

void init () {
	glClearColor(1.0,1.0,1.0,0);
	glColor3f(0.0,0.0,0.0);
	gluOrtho2D(0 , 640 , 0 , 480);
}

float roundVal(float v) {
  return floor(v + 0.5);
}

void onKeyPressCallback (unsigned char key, int x, int y) {
	if (key == 32) {
		glClear(GL_COLOR_BUFFER_BIT);
		glutSwapBuffers();

		windowCleared = true;
		firstMouseClick = false;
	}
}

void drawLineDDA () {
	float fx = first.x, fy = first.y;

	double dx = second.x - fx;
	double dy = second.y - fy;
	double steps = (abs(dx) > abs(dy)) ? abs(dx) : abs(dy);	// if dx > dy, steps = dx else steps = dy, ALLOW truncation

	float xIncrement = dx / (float)steps;
	float yIncrement = dy / (float)steps;

	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);

	glVertex2d(fx, fy);

	for (int i = 0; i < steps; i++) {
		fx += xIncrement;
		fy += yIncrement;

		glVertex2d(roundVal(fx), roundVal(fy));
	}

	glEnd();
	glFlush();
	windowCleared = false;
}

void onMouseClickCallback(int button, int state, int x, int y) {	
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
    	if (!windowCleared) {
			cout << "Press space bar to clear the window first!!!" << endl;
			return;
		}

        if (!firstMouseClick) {
        	firstMouseClick = true;
        	first.x = x;
        	first.y = 480 - y;
        	cout << "First click" << endl;
        } else {
        	firstMouseClick = false;
        	second.x = x;
        	second.y = 480 - y;
        	cout << "Second click" << endl;

        	drawLineDDA();
        }
    }
}

int main (int argc, char *argv[]) {
	first.x = 0;
	first.y = 0;
	second.x = 640;
	second.y = 480;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	glutInitWindowSize(640, 480);
	glutInitWindowPosition(0, 0);

	glutCreateWindow("DDA Line generation algorithm");
	init();
	
	glutKeyboardFunc(onKeyPressCallback);
	glutMouseFunc(onMouseClickCallback);
	glutDisplayFunc(drawLineDDA);
	glutMainLoop();

	return 0;
}

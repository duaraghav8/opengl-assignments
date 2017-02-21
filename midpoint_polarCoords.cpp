#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <cmath>
#include <iostream>

using namespace std;

struct Coord { float x, y; };

void init () {
	glClearColor(1.0,1.0,1.0,0);
	glColor3f(0.0,0.0,0.0);
	gluOrtho2D(0 , 1000, 0 , 600);
}

void onWindowResize (int h, int w) {
	glutPostRedisplay();
}

void midpointCircle (Coord centerPoint, float radius) {
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);

	float X = radius, Y = 0.0f;
	float error = 0.0f;

	while (X >= Y) {
		glVertex2d (centerPoint.x + X, centerPoint.y + Y);
		glVertex2d (centerPoint.x + Y, centerPoint.y + X);
		glVertex2d (centerPoint.x - Y, centerPoint.y + X);
		glVertex2d (centerPoint.x - X, centerPoint.y + Y);
		glVertex2d (centerPoint.x - X, centerPoint.y - Y);
		glVertex2d (centerPoint.x - Y, centerPoint.y - X);
		glVertex2d (centerPoint.x + Y, centerPoint.y - X);
		glVertex2d (centerPoint.x + X, centerPoint.y - Y);

		if (error > 0.0f) {
			X -= 1;
			error -= 2*X + 1;
		} else {
			Y += 1;
			error += 2*Y + 1;
		}
	}

	glEnd();
	glFlush();
}


void drawEllipse (float xc, float yc, float x, float y) {
	glVertex2d(xc+x, yc+y);
	glVertex2d(xc-x, yc+y);
	glVertex2d(xc+x, yc-y);
	glVertex2d(xc-x, yc-y);
}

void midpointEllipse (Coord centerPoint, float rx, float ry) {
	float rxSquare = rx*rx;
	float rySquare = ry*ry;
	float X = 0.0f, Y = ry, P;
	float PX = 0.0f, PY = 2*Y*rxSquare;
}

void createShapes () {
	Coord centerPoint;

	centerPoint.x = 300.0f;
	centerPoint.y = 300.0f;

	midpointCircle (centerPoint, 60.0f);
}

int main (int argc, char *argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	glutInitWindowSize(1000, 600);
	glutInitWindowPosition(0, 0);

	glutCreateWindow("Oval generation using Midpoint & Polar Coords Algorithms");
	init();
	
	glutDisplayFunc(createShapes);
	glutReshapeFunc(onWindowResize);
	glutMainLoop();

	return 0;
}

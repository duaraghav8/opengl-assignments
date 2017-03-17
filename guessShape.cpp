/*
	Mark 4 points and the program will try to guess whether the points closely resemble a Rectangle / Square or no quadrilateral.
	COMPILE: g++ guessShape.cpp -o guessShape -lGL -lGLU -lglut
*/




#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <cmath>
#include <iostream>

using namespace std;

struct Coords {
	double x, y;
};


//**************************************************
/*
	TO create a Coords object,

	Coords a;

	a.x = 100;
	a.y = 90.23;

	call getShape():

	getShape (a, b, c, d)
	where a, b, c, d are Coords objects obtained after user mouse click.
*/

double getDistance (Coords a, Coords b) {
	return sqrt (pow ((b.y - a.y), 2) + pow ((b.x - a.x), 2));
}

bool isInCloseProximity (double d1, double d2) {
	return abs (d1 - d2) <= 30.0;
}

bool areCoordsAligned (double a, double b) {
	return abs (a - b) <= 20.0;
}

void getShape (Coords a, Coords b, Coords c, Coords d) {
	double ab = getDistance (a, b), ac = getDistance (a, c), ad = getDistance (a, d);
	double bc = getDistance (b, c), bd = getDistance (b, d);
	double cd = getDistance (c, d);

	if (
		isInCloseProximity (ab, cd) && isInCloseProximity (bc, ad) &&
		areCoordsAligned (a.x, d.x) && areCoordsAligned (b.x, c.x)
	) {
		if (isInCloseProximity (ab, bc)) {
			cout << "SHAPE IS A POTENTIAL SQUARE" << endl;
		} else {
			cout << "SHAPE IS A POTENTIAL RECTANGLE" << endl;
		}
	} else {
		cout << "DOESN'T SEEM LIKE A VALID SHAPE" << endl;
	}
}
//**************************************************




struct Coords a, b, c, d;
int mouseClickFlag = 0;

void init () {
	glClearColor(1.0,1.0,1.0,0);
	glColor3f(0.0,0.0,0.0);
	gluOrtho2D(0 , 640 , 0 , 480);
}

void display () {
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush ();
}

void onMouseClickCallback(int button, int state, int x, int y) {	
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
    	y = 480 - y;
		glBegin(GL_POINTS);
		glVertex2d(x, y);
		glVertex2d(x+1, y+1);
		glVertex2d(x-1, y-1);
		glVertex2d(x+1, y-1);
		glVertex2d(x-1, y+1);
		glVertex2d(x+1, y);
		glVertex2d(x-1, y);
		glVertex2d(x, y+1);
		glVertex2d(x, y-1);
		glEnd();
		glFlush();

    	switch (mouseClickFlag) {
    		case 0:
    			a.x = x;
    			a.y = y;
    			break;
    		case 1:
    			b.x = x;
    			b.y = y;    		
    			break;
    		case 2:
    			c.x = x;
    			c.y = y; 
    			break;
    		case 3:
    			d.x = x;
    			d.y = y;
    			mouseClickFlag = -1;
    			getShape (a, b, c, d);
    			break;	
    	}

    	mouseClickFlag++;
    }
}

int main (int argc, char *argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	glutInitWindowSize(640, 480);
	glutInitWindowPosition(0, 0);

	glutCreateWindow("Shape Guessing Algorithm");
	init();

	glutMouseFunc(onMouseClickCallback);
	glutDisplayFunc(display);
	glutMainLoop();

	return 0;
}

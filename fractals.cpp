#include <cstdlib>
#include <cmath>
#include <vector>
#include <iostream>
#include <fstream>
#include <GL/glut.h>
#include <GL/freeglut.h>

#define ROOT3 1.73205081
#define ONEBYROOT3 0.57735027

using namespace std;

static int maxLevel = 0; 

class Source; 

class Sequel
{
public:
   Sequel() { coords.clear(); v.clear(); }
   void drawKochOrVariant();
   friend class Source;

private:
   vector<float> coords; // Vector of x, y co-ordinates of points specifying sequel object.
   vector<Source> v; // Vector of associated source objects to be produced recursively.
};

void Sequel::drawKochOrVariant()
{
   glBegin(GL_LINE_STRIP);
   for (int i=0; i < 5; i++)
      glVertex2f(coords[2*i], coords[2*i+1]);
   glEnd();
}

class Source
{
public:
   Source(){ }
   Source(float coordsVal[4])
   {
      for (int i=0; i < 4; i++) coords[i] = coordsVal[i];
   }

   void draw(); // Routine to draw source line segment.

   Sequel sourceToSequelKoch(); // Routine to generate Sequel object in case of Koch snowflake.
   void produceKoch(int level);

   friend class Sequel;

private:
   float coords[4]; //co-ordinates of a line segment endpoints
};

void Source::draw()
{
   glBegin(GL_LINES);
   for (int i=0; i < 2; i++)
      glVertex2f(coords[2*i], coords[2*i+1]);
   glEnd();
}

// Routine to generate Sequel object in case of Koch snowflake.
Sequel Source::sourceToSequelKoch()
{
   float x0, y0, x1, y1, coordsVal[10], coordsVal1[4];
   int i, j;
   Source s;
   Sequel seq = *new Sequel();

   x0 = coords[0]; y0 = coords[1]; x1 = coords[2]; y1 = coords[3];
   coordsVal[0] = x0;
   coordsVal[1] = y0;
   coordsVal[2] = 0.66666667*x0 + 0.33333333*x1;
   coordsVal[3] = 0.66666667*y0 + 0.33333333*y1;
   coordsVal[4] = 0.5*(x0 + x1) - 0.5*ONEBYROOT3*(y1 - y0);
   coordsVal[5] = 0.5*(y0 + y1) + 0.5*ONEBYROOT3*(x1 - x0);
   coordsVal[6] = 0.33333333*x0 + 0.66666667*x1;
   coordsVal[7] = 0.33333333*y0 + 0.66666667*y1;
   coordsVal[8] = x1;
   coordsVal[9] = y1;

   // Enter Koch polyline vertices into sequel object.
   for (i=0; i < 10; i++) seq.coords.push_back(coordsVal[i]);

   // Specify all 4 segments of the Koch polyline for recursive production.
   for (i=0; i < 4; i++)
   {
      for (j=0; j < 4; j++)
	  {
	     coordsVal1[j] = coordsVal[2*i+j];
	  }
	  s = *new Source(coordsVal1);
	  seq.v.push_back(s);
   }

   return seq;
}

void Source::produceKoch(int level)
{  //REcursion
   glColor3f(1.0, 1.0, 1.0);
   if (maxLevel == 0) 
      this->draw();
   else if (maxLevel == 1)
       this->sourceToSequelKoch().drawKochOrVariant();
   else if (level < maxLevel-1)
	     for (int i=0; i < 4; i++) 
          this->sourceToSequelKoch().v[i].produceKoch(level+1);	
   else 
      this->sourceToSequelKoch().drawKochOrVariant();                                
}


void display()
{  
   glClear(GL_COLOR_BUFFER_BIT);
   
   glColor3f(1.0,1.0,1.0);
   glRasterPos2f(-10,40);
   glutBitmapString(GLUT_BITMAP_HELVETICA_18,(const unsigned char*)"Raghav Dua 500038780");
   glColor3f(1.0,1.0,1.0);
   glRasterPos2f(-10,-40);
   glutBitmapString(GLUT_BITMAP_HELVETICA_18,(const unsigned char*)"Snowflake Fractal");


   glColor3f(1.0, 1.0, 1.0);
   float coordsVal1[4] = {-30.0, -15.0, 0.0, -15.0 + ROOT3*0.5*60.0}; 
   float coordsVal2[4] = {0.0, -15.0 + ROOT3*0.5*60.0, 30.0, -15.0};
   float coordsVal3[4] = {30.0, -15.0, -30.0, -15.0}; 

   Source src1 = *new Source(coordsVal1); 
   Source src2 = *new Source(coordsVal2);
   Source src3 = *new Source(coordsVal3); 

      src1.produceKoch(0);
      src2.produceKoch(0);
      src3.produceKoch(0);

   glFlush();
}

void setup(void) 
{
   glClearColor(0.0, 0.0, 0.0, 0.0);
}

void resize(int w, int h)
{
   glViewport(0, 0, (GLsizei)w, (GLsizei)h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(-50.0, 50.0, -50.0, 50.0, -1.0, 1.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

void keyInput(unsigned char key, int x, int y)
{
   switch(key) 
   {
      case 27:
         exit(0);
         break;
      default:
         break;
   }
}

void specialKeyInput(int key, int x, int y)
{
   if (key == GLUT_KEY_UP) maxLevel++;
   if( key == GLUT_KEY_DOWN) 
      if (maxLevel > 0) maxLevel--;
   glutPostRedisplay();
}

int main(int argc, char **argv) 
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
   glutInitWindowSize(900, 700);
   glutInitWindowPosition(100, 100); 
   glutCreateWindow("Snowflake Fractal");
   setup(); 
   glutDisplayFunc(display); 
   glutReshapeFunc(resize);  
   glutKeyboardFunc(keyInput);
   glutSpecialFunc(specialKeyInput);
   glutMainLoop(); 
   return 0;  
}

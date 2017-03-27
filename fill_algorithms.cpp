#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include <cstring>
#include <string>

using namespace std;

int winIdMain;
int winIdSub, winIdSub2;

typedef struct pix
{
    float r,g,b;
}pix;

void printb(string c, int x, int y)
{
    glRasterPos2i(x, y);
    glColor3f(1.0, 1.0, 1.0);
    for(int i=0;i<c.length();i++)
      glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,c[i]);
    glFlush();
}

void floodDis()
{  // printb("Flood-Fill",680,670);
    glColor3f(1.0,1.0,1.0);
    glBegin(GL_LINE_LOOP);
    glVertex2i(300,300);
    glVertex2i(300,400);
    glVertex2i(400,400);
    glVertex2i(400,300);
    glEnd();
    glFlush();
}

void boundDis()
{ //  printb("Boundary-Fill",10,670);
    glColor3f(1.0,1.0,1.0);
    glBegin(GL_LINE_LOOP);
    glVertex2i(300,300);
    glVertex2i(300,400);
    glVertex2i(400,400);
    glVertex2i(400,300);
    glEnd();
    glFlush();
}


void FloodFill(int a, int b, pix neww, pix old)
{
    pix tem;
    glReadPixels(a,b,1,1,GL_RGB,GL_FLOAT,&tem);
    printf("%f %f %f\n",tem.r,tem.g,tem.b);

    if((tem.r==old.r)&&(tem.g==old.g)&&(tem.b==old.b))
    {
        glBegin(GL_POINTS);
        glColor3f(neww.r,neww.g,neww.b);
        glVertex2i(a,b);
        glEnd();
        glFlush();

        FloodFill(a+1,b,neww,old);
        FloodFill(a-1,b,neww,old);
        FloodFill(a,b+1,neww,old);
        FloodFill(a,b-1,neww,old);
    }

}

void boundFill(int a, int b, pix fil, pix boun)
{
    pix tem;
    glReadPixels(a,b,1,1,GL_RGB,GL_FLOAT,&tem);
    //printf("%f %f %f\n",tem.r,tem.g,tem.b);

    if((tem.r!=boun.r)&&(tem.g!=boun.g)&&(tem.b!=boun.b)&&(tem.r!=fil.r)&&(tem.g!=fil.g)&&(tem.b!=fil.b))
    {
        glBegin(GL_POINTS);
        glColor3f(fil.r,fil.g,fil.b);
        glVertex2i(a,b);
        glEnd();
        glFlush();

        boundFill(a+1,b,fil,boun);
        boundFill(a-1,b,fil,boun);
        boundFill(a,b+1,fil,boun);
        boundFill(a,b-1,fil,boun);
    }

}

void floo(int button, int state, int x, int y)
{
    printf("fl %d %d\n",x,y);
    pix fi,bo;
    fi.r=0.1;
    fi.g=0.1;
    fi.b=1.0;

    bo.r=0.0;
    bo.g=0.0;
    bo.b=0.0;

    int xi = x;
    int yi = (660-y);

    FloodFill(xi,yi,fi,bo);
}

void boun(int button, int state, int x, int y)
{
    printf("bo %d %d\n",x,y);

    pix fi,bo;
    fi.r=0.8;
    fi.g=0.001;
    fi.b=0.8;

    bo.r=1.0;
    bo.g=1.0;
    bo.b=1.0;
   /* if((x>=300 && x<=400) && (y>=300 && y <=400))
        {
          glClear(GL_COLOR_BUFFER_BIT);
          printb("Invalid",200,150);

         }
    else{    */
          int xi = x;
          int yi = (660-y);
          boundFill(xi,yi,fi,bo);
       // }
}

void clear () {
  glClear(GL_COLOR_BUFFER_BIT);
  glFlush ();
}

void mainDis()
{
  glutSetWindow (winIdMain);
  printb("Boundary-Fill",10,660);
  printb("Flood-Fill",680,660);
 printb("Raghav Dua",1170,680);
 printb("500038780",1170,660);

}

void init()
{
  glClearColor(0.15,0.15,0.15,1);
  glColor3f(0.5,0.5,0.5);
  gluOrtho2D(0,1300,0,700);
  glViewport(0, 0, 1300, 700);
}

int main(int argc, char **argv)
{
  glutInit (&argc, argv);
  glutInitDisplayMode (GLUT_SINGLE | GLUT_RGBA);
  glutInitWindowPosition (0, 0);
  glutInitWindowSize (1300, 700);

  winIdMain = glutCreateWindow ("The OpenGL");
  init();
  clear ();
  glutDisplayFunc (mainDis);

  winIdSub = glutCreateSubWindow(winIdMain, 10, 100, 650 , 650 );
  gluOrtho2D(0,650,0,650);
  glClearColor(0.25,0.25,0.25,1);
  glutDisplayFunc (boundDis);
  glutMouseFunc(boun);

  winIdSub2 = glutCreateSubWindow(winIdMain, 670, 100, 650 , 650 );
  gluOrtho2D(0,650,0,650);
  glClearColor(0.25,0.25,0.25,1);
  glutDisplayFunc (floodDis);
  glutMouseFunc(floo);

  glutMainLoop ();

}

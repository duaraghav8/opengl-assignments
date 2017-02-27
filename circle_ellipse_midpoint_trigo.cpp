#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

int winIdMain;
int winIdSub, winIdSub2, winIdSub3, winIdSub4;
int GLOBAL_HEIGHT = 768, GLOBAL_WIDTH = 1368;
int GAP = 10;

void mainD()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
    glVertex2i(5,5);
    glEnd();
    glFlush();
}

void OneD()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
    double x,y;
    for (int i = 0; i < 1000; i++)
    {
    x = 2* cos(2*3.14159*i/1000);
    y = 2* sin(2*3.14159*i/1000);
    glVertex3f(x,y,0);

    }
    glEnd();
    glFlush();
}

void TwoD()
{
    glClear(GL_COLOR_BUFFER_BIT);

    int r=(.1172 * GLOBAL_HEIGHT);
    int x=0,y=r, p=1-r;
    glEnable(GL_POINT_SIZE);
    while(x<=y)
    {
        glBegin(GL_POINTS);
        glVertex2i(x,y);
        glVertex2i(y,x);
        glVertex2i(-x,y);
        glVertex2i(-x,-y);
        glVertex2i(-y,x);
        glVertex2i(-y,-x);
        glVertex2i(y,-x);
        glVertex2i(x,-y);
        glEnd();
        glFlush();
        if(p<0)
        {
            p=p+2*x+3;
        }
        else
        {
            p=p+2*(x-y)+5;
            y--;
        }
        x++;
}
}

void ThreeD()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
    double x,y;
    for (int i = 0; i < 1000; i++)
    {
    x = 2* cos(2*3.14159*i/1000);
    y = 3* sin(2*3.14159*i/1000);
    glVertex3f(y,x,0);

    }
    glEnd();
    glFlush();
}

void FourD()
{
    glClear(GL_COLOR_BUFFER_BIT);
        float rx=(.1023 * GLOBAL_WIDTH), ry=(.1172 * GLOBAL_HEIGHT);
        float rxSq = rx * rx;
        float rySq = ry * ry;
        float x = 0, y = ry, p;
        float px = 0, py = 2 * rxSq * y;
         glEnable(GL_POINT_SIZE);
         glBegin(GL_POINTS);
         glVertex2d(+x,-y);
         glVertex2d(-x,-y);
         glVertex2d(-x,+y);
        glEnd();

        p = rySq - (rxSq * ry) + (0.25 * rxSq);
        while (px < py)
        {
                        x++;
                        px = px + 2 * rySq;
                        if (p < 0)
                        p = p + rySq + px;
                        else
                        {
                        y--;
                        py = py - 2 * rxSq;
                        p = p + rySq + px - py;
                        }
                         glBegin(GL_POINTS);

                         glVertex2d(+x,+y);
                         glVertex2d(+x,-y);
                         glVertex2d(-x,-y);
                         glVertex2d(-x,+y);
                        glEnd();

        }

        p = rySq*(x+0.5)*(x+0.5) + rxSq*(y-1)*(y-1) - rxSq*rySq;
        while (y > 0)
        {
                y--;
                py = py - 2 * rxSq;
                if (p > 0)
                p = p + rxSq - py;
                else
                {
                x++;
                px = px + 2 * rySq;
                p = p + rxSq - py + px;
                }
               glBegin(GL_POINTS);

         glVertex2d(+x,+y);
         glVertex2d(+x,-y);
         glVertex2d(-x,-y);
         glVertex2d(-x,+y);
        glEnd();
        glFlush();

        }
}

void reshape(int width,  int height)
{
    GLOBAL_HEIGHT = height, GLOBAL_WIDTH = width;
    glViewport(0, 0, width, height);
    glOrtho(0.0,width,height,0,-1.0,1.0);

    float sub_width = (.475*GLOBAL_WIDTH);
    float sub_height = (.429*GLOBAL_HEIGHT);

    glutSetWindow(winIdSub);
    glutPositionWindow(GAP, GAP);
    glutReshapeWindow(sub_width, sub_height);

    glutSetWindow(winIdSub2);
    glutPositionWindow(sub_width+20, GAP);
    glutReshapeWindow(sub_width, sub_height);

    glutSetWindow(winIdSub3);
    glutPositionWindow(GAP, sub_height+20);
    glutReshapeWindow(sub_width, sub_height);

    glutSetWindow(winIdSub4);
    glutPositionWindow(sub_width+20, sub_height+20);
    glutReshapeWindow(sub_width, sub_height);


}



void init()
{
  glClearColor(0.15,0.15,0.15,1);
  glColor3f(0.0,0.0,0.0);
  glOrtho(0.0, GLOBAL_WIDTH,GLOBAL_HEIGHT,0,-1.0,1.0);
  glViewport(0, 0, GLOBAL_WIDTH, GLOBAL_HEIGHT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
}

int main(int argc, char **argv)
{
  glutInit (&argc, argv);
  glutInitDisplayMode (GLUT_SINGLE | GLUT_RGBA);
  glutInitWindowPosition (0, 0);
  glutInitWindowSize (GLOBAL_WIDTH, GLOBAL_HEIGHT);

  winIdMain = glutCreateWindow ("Circle & Ellipse - Midpoint & Trigo algorithms");
  init();
  glutDisplayFunc (mainD);
  glutReshapeFunc(reshape);

  winIdSub = glutCreateSubWindow(winIdMain, GAP, GAP, (.475*GLOBAL_WIDTH) , (.429*GLOBAL_HEIGHT) );
  gluOrtho2D(-5,5,-2.75,2.75);
  glClearColor(0.25,0.25,0.25,1);
  glutDisplayFunc (OneD);

  winIdSub2 = glutCreateSubWindow(winIdMain, (.475*GLOBAL_WIDTH)+20, GAP, (.475*GLOBAL_WIDTH) , (.429*GLOBAL_HEIGHT) );
  gluOrtho2D(-250,250,-138,138);
  glClearColor(0.25,0.25,0.25,1);
  glutDisplayFunc (TwoD);

  winIdSub3 = glutCreateSubWindow(winIdMain, GAP, (.429*GLOBAL_HEIGHT)+20, (.475*GLOBAL_WIDTH) , (.429*GLOBAL_HEIGHT) );
  gluOrtho2D(-5,5,-2.75,2.75);
  glClearColor(0.25,0.25,0.25,1);
  glutDisplayFunc (ThreeD);

  winIdSub4 = glutCreateSubWindow(winIdMain, (.475*GLOBAL_WIDTH)+20, (.429*GLOBAL_HEIGHT)+20, (.475*GLOBAL_WIDTH) , (.429*GLOBAL_HEIGHT) );
  gluOrtho2D(-250,250,-138,138);
  glClearColor(0.25,0.25,0.25,1);
  glutDisplayFunc (FourD);

  glutMainLoop ();

}

#include "screencasts.h"
#include <bits/stdc++.h>

using namespace std;
int com = 0,rot = 1;
 int explode = 0;
vector<char> steps;
int pos[28] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27};
#include "exp.h"
/*  Poor man's approximation of PI */
#define PI 3.1415926535898
/*  Macro for sin & cos in degrees */
#define Cos(th) cos(PI/180*(th))
#define Sin(th) sin(PI/180*(th))

vector<pair<int,char> > v[28];
vector<pair<int,char> > a[28];


/*  Globals */

double dim=3.0; /* dimension of orthogonal box */
char *windowName = "OpenGL screenscasts 7: Drawing in 3d part 2: Cubes, Perspective and Orthogonal Projections";
int windowWidth=500;
int windowHeight=450;

/*  Various global state */
int toggleAxes = 0;   /* toggle axes on and off */
int toggleValues = 1; /* toggle values on and off */
int toggleMode = 0; /* projection mode */
int th = 0;   /* azimuth of view angle */
int ph = 0;   /* elevation of view angle */
int fov = 55; /* field of view for perspective */
int asp = 1;  /* aspect ratio */

/*  Cube vertices */
GLfloat vertA[3] = { 0.5, 0.5, 0.5};
GLfloat vertB[3] = {-0.5, 0.5, 0.5};
GLfloat vertC[3] = {-0.5,-0.5, 0.5};
GLfloat vertD[3] = { 0.5,-0.5, 0.5};
GLfloat vertE[3] = { 0.5, 0.5,-0.5};
GLfloat vertF[3] = {-0.5, 0.5,-0.5};
GLfloat vertG[3] = {-0.5,-0.5,-0.5};
GLfloat vertH[3] = { 0.5,-0.5,-0.5};


GLfloat red[3] = { 1, 0.0, 0.0};
GLfloat blue[3] = {0.0, 0.0, 1};
GLfloat green[3] = {0,1,0 };
GLfloat white[3] = { 1,1,1};
GLfloat yellow[3] = { 1, 1,0};
GLfloat orange[3] = {1, 128/255.0,0};
GLfloat grey[3] = {96/255.0,96/255.0,96/255.0};

/*
 * project()
 * ------
 * Sets the projection
 */
void project()
{
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  if (toggleMode) {
    /* perspective */
    gluPerspective(fov,asp,dim/4,4*dim);
  }
  else {
    /* orthogonal projection*/
    glOrtho(-dim*asp,+dim*asp, -dim,+dim, -dim,+dim);
  }

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

/*
 * drawAxes()
 * ------
 * Draw the axes
 */
void drawAxes()
{
  if (toggleAxes) {
    /*  Length of axes */
    double len = 2.0;
    glColor3f(1.0,1.0,1.0);
    glBegin(GL_LINES);
    glVertex3d(0,0,0);
    glVertex3d(len,0,0);
    glVertex3d(0,0,0);
    glVertex3d(0,len,0);
    glVertex3d(0,0,0);
    glVertex3d(0,0,len);
    glEnd();
    /*  Label axes */
    glRasterPos3d(len,0,0);
    print("X");
    glRasterPos3d(0,len,0);
    print("Y");
    glRasterPos3d(0,0,len);
    print("Z");
  }
}

/*
 *  drawValues()
 *  ------
 *  Draw the values in the lower left corner
 */
void drawValues()
{
  if (toggleValues) {
    glColor3f(0.8,0.8,0.8);
    printAt(5,5,"View Angle (th, ph) =(%d, %d)", th,ph);
    printAt(5,25,"Projection mode =(%s)", toggleMode?"Perspective":"Orthogonal");
    /*glRasterPos3fv(vertA);
    print("A");
    glRasterPos3fv(vertB);
    print("B");
    glRasterPos3fv(vertC);
    print("C");
    glRasterPos3fv(vertD);
    print("D");
    glRasterPos3fv(vertE);
    print("E");
    glRasterPos3fv(vertF);
    print("F");
    glRasterPos3fv(vertG);
    print("G");
    glRasterPos3fv(vertH);
    print("H");*/
  }
}

/*
 *  drawShape()
 *  ------
 *  Draw the GLUT shape
 */
void drawCube(GLfloat* top,GLfloat* fronti,GLfloat* left,GLfloat* right,GLfloat* backi,GLfloat* down)
{
  /* Cube */
  glBegin(GL_QUADS);
  /* front => ABCD yellow */

            glColor3fv(fronti);


  glVertex3fv(vertA);
  glVertex3fv(vertB);
  glVertex3fv(vertC);
  glVertex3fv(vertD);
  /* back => FEHG red */
  //glColor3f(1.0,0.0,0.0);
              glColor3fv(backi);

  glVertex3fv(vertF);
  glVertex3fv(vertE);
  glVertex3fv(vertH);
  glVertex3fv(vertG);
  /* right => EADH green */
  //glColor3f(0.0,1.0,0.0);

              glColor3fv(right);

  glVertex3fv(vertE);
  glVertex3fv(vertA);
  glVertex3fv(vertD);
  glVertex3fv(vertH);
  /* left => BFGC blue */
  //glColor3f(0.0,0.0,1.0);
              glColor3fv(left);


  glVertex3fv(vertB);
  glVertex3fv(vertF);
  glVertex3fv(vertG);
  glVertex3fv(vertC);
  /* top => EFBA turquoise */
  //glColor3f(0.0,1.0,1.0);

             glColor3fv(top);

  glVertex3fv(vertE);
  glVertex3fv(vertF);
  glVertex3fv(vertB);
  glVertex3fv(vertA);
  /* bottom => DCGH pink */
  //glColor3f(1.0,0.0,1.0);
             glColor3fv(down);

  glVertex3fv(vertD);

  glVertex3fv(vertC);
  glVertex3fv(vertG);
  glVertex3fv(vertH);
  glEnd();
}

void precal(int i)
{


    int sp = 2;
    int n = v[i].size();
    if(n != 0)
    {

      if(v[i][n-1].second == 'z')
        {
            glRotatef(v[i][n-1].first,0,0,1);

        }
        if(v[i][n-1].second == 'y')
        {
            glRotatef(v[i][n-1].first,0,1,0);

        }
        if(v[i][n-1].second == 'x')
        {
            glRotatef(v[i][n-1].first,1,0,0);
        }
    for(int j = n-2;j>=0;j--)
    {
        if(v[i][j].second == 'z')
        {
            glRotatef(a[i][j].first,0,0,1);

        }
        if(v[i][j].second == 'y')
        {
            glRotatef(a[i][j].first,0,1,0);

        }
        if(v[i][j].second == 'x')
        {
            glRotatef(a[i][j].first,1,0,0);
        }
    }


    if(v[i][n-1].first != a[i][n-1].first)
    {
    v[i][n-1].first+=sp*(a[i][n-1].first-v[i][n-1].first)/abs(a[i][n-1].first-v[i][n-1].first);
    }

}
}



void drawShape()
{
    //front face
double off = .05;
double sp = 2;
int i;
glPushMatrix();
glScalef(.7,.7,.7);
if(com == 1 && rot<=400)
{glRotatef(rot,0,1,0);
rot+=1;
if(rot>= 400)
    explode = 1;
                printAt(100,100,"SOLVED!!! NOW WAIT FOR IT!!");

    newExplosion();

}
if(rot>=10000)
    {
            printAt(100,100,"SOLVED!!! NOW WAIT FOR IT!!");

        return;
    }
/***********back face**********/
glPushMatrix();

glPushMatrix();
i = 23;
precal(i);
glTranslatef(0,0,1+off-2-2*off);//23
drawCube(grey,grey,grey,grey,yellow,grey);
glPopMatrix();

glPushMatrix();
i = 24;
precal(i);
glTranslatef(1+off,0,1+off-2-2*off);//24
drawCube(grey,grey,grey,orange,yellow,grey);
glPopMatrix();

glPushMatrix();
i = 21;
precal(i);

glTranslatef(1+off,1+off,1+off-2-2*off);//21
drawCube(red,grey,grey,orange,yellow,grey);
glPopMatrix();


glPushMatrix();
i = 19;
precal(i);


glTranslatef(-1-off,1+off,1+off-2-2*off);//19
drawCube(red,grey,green,grey,yellow,grey);
glPopMatrix();

glPushMatrix();
i = 20;
precal(i);

glTranslatef(0,1+off,1+off-2-2*off);//20
drawCube(red,grey,grey,grey,yellow,grey);
glPopMatrix();

glPushMatrix();
i = 25;
precal(i);

glTranslatef(-1-off,-1-off,1+off-2-2*off);//25
drawCube(grey,grey,green,grey,yellow,white);
glPopMatrix();

glPushMatrix();
i = 22;
precal(i);


glTranslatef(-1-off,0,1+off-2-2*off);//22
drawCube(grey,grey,green,grey,yellow,grey);
glPopMatrix();

glPushMatrix();
i = 26;
precal(i);

glTranslatef(0,-1-off,1+off-2-2*off);//26
drawCube(grey,grey,grey,grey,yellow,white);
glPopMatrix();

glPushMatrix();
i = 27;
precal(i);


glTranslatef(1+off,-1-off,1+off-2-2*off);//27
drawCube(grey,grey,grey,orange,yellow,white);
glPopMatrix();
glPopMatrix();
/**********mid face************/
glPushMatrix();

glPushMatrix();
i = 14;
precal(i);

glTranslatef(0,0,1+off-1-off);//14
drawCube(red,blue,green,orange,yellow,white);
glPopMatrix();

glPushMatrix();
i = 15;
precal(i);

glTranslatef(1+off,0,1+off-1-off);//15

drawCube(grey,grey,green,orange,grey,grey);
glPopMatrix();

glPushMatrix();
i = 12;
precal(i);

glTranslatef(1+off,1+off,1+off-1-off);//12
drawCube(red,grey,grey,orange,grey,grey);
glPopMatrix();


glPushMatrix();
i = 10;
precal(i);

glTranslatef(-1-off,1+off,1+off-1-off);//10
drawCube(red,grey,green,grey,grey,grey);
glPopMatrix();

glPushMatrix();
i = 11;
precal(i);

glTranslatef(0,1+off,1+off-1-off);//11
drawCube(red,grey,grey,grey,grey,grey);
glPopMatrix();

glPushMatrix();
i = 16;
precal(i);

glTranslatef(-1-off,-1-off,1+off-1-off);//16
drawCube(grey,grey,green,grey,grey,white);
glPopMatrix();

glPushMatrix();
i = 13;
precal(i);

glTranslatef(-1-off,0,1+off-1-off);//13
drawCube(grey,grey,green,grey,grey,grey);
glPopMatrix();

glPushMatrix();
i = 17;
precal(i);

glTranslatef(0,-1-off,1+off-1-off);//17
drawCube(grey,grey,grey,grey,grey,white);
glPopMatrix();

glPushMatrix();
i = 18;
precal(i);

glTranslatef(1+off,-1-off,1+off-1-off);//18
drawCube(grey,grey,grey,orange,grey,white);
glPopMatrix();
glPopMatrix();
/********front face***********/
glPushMatrix();
i = 5;
precal(i);


glTranslatef(0,0,1+off);//5
drawCube(grey,blue,grey,grey,yellow,grey);
glPopMatrix();

glPushMatrix();
i = 6;
precal(i);

glTranslatef(1+off,0,1+off);//6
drawCube(grey,blue,grey,orange,grey,grey);
glPopMatrix();

glPushMatrix();
i = 3;
precal(i);

glTranslatef(1+off,1+off,1+off);//3
drawCube(red,blue,grey,orange,grey,grey);
glPopMatrix();


glPushMatrix();
i = 1;
precal(i);

glTranslatef(-1-off,1+off,1+off);//1
drawCube(red,blue,green,grey,grey,grey);
glPopMatrix();

glPushMatrix();
i = 2;
precal(i);

glTranslatef(0,1+off,1+off);//2
drawCube(red,blue,grey,grey,grey,grey);
glPopMatrix();

glPushMatrix();
i = 7;
precal(i);


glTranslatef(-1-off,-1-off,1+off);//7
drawCube(grey,blue,green,grey,grey,white);
glPopMatrix();

glPushMatrix();
i = 4;
precal(i);


glTranslatef(-1-off,0,1+off);//4
drawCube(grey,blue,green,grey,grey,grey);
glPopMatrix();


glPushMatrix();
i = 8;
precal(i);


glTranslatef(0,-1-off,1+off);//8
drawCube(grey,blue,grey,grey,grey,white);
glPopMatrix();

glPushMatrix();
i = 9;
precal(i);

glTranslatef(1+off,-1-off,1+off);//9
drawCube(grey,blue,grey,orange,grey,white);
glPopMatrix();
glPopMatrix();

}

/*
 *  display()
 *  ------
 *  Display the scene
 */
void display()
{
  /*  Clear the image */
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  /*  Enable Z-buffering in OpenGL */
  glEnable(GL_DEPTH_TEST);

  /*  Reset previous transforms */
  glLoadIdentity();
  if(explode)
  {
      display2();
      idle();
      return;
  }
  /*  Perspective - set eye position */
  if (toggleMode) {
    double Ex = -2*dim*Sin(th)*Cos(ph);
    double Ey = +2*dim        *Sin(ph);
    double Ez = +2*dim*Cos(th)*Cos(ph);
    /* camera/eye position, aim of camera lens, up-vector */
    gluLookAt(Ex,Ey,Ez , 0,0,0 , 0,Cos(ph),0);
  }
  /*  Orthogonal - set world orientation */
  else {
    glRotatef(ph,1,0,0);
    glRotatef(th,0,1,0);
  }

  /*  Draw  */
  drawAxes();
  drawValues();
  drawShape();

  /*  Flush and swap */
  glFlush();
  glutSwapBuffers();
}
/*
 *  reshape()
 *  ------
 *  GLUT calls this routine when the window is resized
 */
void reshape(int width,int height)
{
  asp = (height>0) ? (double)width/height : 1;
  glViewport(0,0, width,height);
  project();
}

/*
 *  windowKey()
 *  ------
 *  GLUT calls this routine when a non-special key is pressed
 */
 void reverseface(char f)
{
if(f == 'r')
{
    //steps.push_back('r');
    int marked[28] = {0};
    for(int i = 1;i<= 27;i++)
    {
        if(pos[i]%3 == 0)
            {a[i].push_back(make_pair(-90,'x'));
                    v[i].push_back(make_pair(0,'x'));}

    }

    for(int i = 1;i<=27;i++)
    {
        if(pos[i]%3 == 0 )
        {
            pos[i]=(7*pos[i])%30;
        }
    }


}
else if(f == 'l')
{
     //steps.push_back('l');

    int marked[28] = {0};
    for(int i = 1;i<= 27;i++)
    {
        if(pos[i]%3 == 1)
       {

        a[i].push_back(make_pair(-90,'x'));
                v[i].push_back(make_pair(0,'x'));
    }

    }

    for(int i = 1;i<=27;i++)
    {
        if(pos[i]%3 == 1)
        {
            pos[i]=(7*pos[i]+12)%30;
        }
        //cout<<i<<" "<<pos[i]<<endl;
    }


}
else if(f == 'f')
{
        // steps.push_back('f');

    int marked[28] = {0};
    for(int i = 1;i<= 27;i++)
    {
        if(pos[i]<=9)
        {

            a[i].push_back(make_pair(-90,'z'));
            v[i].push_back(make_pair(0,'z'));
        }


     }

    for(int i = 1;i<=27;i++)
    {
        if(pos[i]<=9)
        {
            pos[i]=(3*pos[i])%10;
        }
        //cout<<i<<" "<<pos[i]<<endl;
    }



}
else if (f == 'd')
{
            // steps.push_back('d');

    int f = 0;
    for(int i = 1;i<= 27;i++)
    {
        f = 0;

        if(pos[i] == 7)
        {            f = 1;


            pos[i] = 25;

        }
         else if(pos[i] == 8)
        {
                        f = 1;

            pos[i] = 16;


        }
        else if(pos[i] == 9)
        {
            f = 1;

            pos[i] = 7;

        }
        else if(pos[i] == 16)
        {
            f = 1;

            pos[i] = 26;

        }
        else if(pos[i] == 17)
        {
                     f = 1;

            pos[i] = 17;

        }
        else if(pos[i] == 18)
        {
                        f = 1;

            pos[i] = 8;

        }
        else if(pos[i] == 25)
        {
                        f = 1;

            pos[i] = 27;

        }
        else if(pos[i] == 27)
        {
                        f = 1;

            pos[i] = 9;

        }
        else if(pos[i] == 26)
        {
            f = 1;
            pos[i] = 18;

        }
        if(f)
        {
             a[i].push_back(make_pair(-90,'y'));
            v[i].push_back(make_pair(0,'y'));
        }


     }


}
else if (f == 't')
{
             //steps.push_back('t');

    int f = 0;
    for(int i = 1;i<= 27;i++)
    {
        f = 0;

        if(pos[i] == 19)
        {            f = 1;


            pos[i] = 21;

        }
         else if(pos[i] == 10)
        {
                        f = 1;

            pos[i] = 20;


        }
        else if(pos[i] == 1)
        {
            f = 1;

            pos[i] = 19;

        }
        else if(pos[i] == 2)
        {
            f = 1;

            pos[i] = 10;

        }
        else if(pos[i] == 3)
        {
                     f = 1;

            pos[i] = 1;

        }
        else if(pos[i] == 12)
        {
                        f = 1;

            pos[i] = 2;

        }
        else if(pos[i] == 21)
        {
                        f = 1;

            pos[i] = 3;

        }
        else if(pos[i] == 20)
        {
                        f = 1;

            pos[i] = 12;

        }
        else if(pos[i] == 11)
        {
            f = 1;
            pos[i] = 11;

        }
        if(f)
        {
             a[i].push_back(make_pair(-90,'y'));
            v[i].push_back(make_pair(0,'y'));
        }


     }


}
else if (f == 'b')
{
             //steps.push_back('b');

    for(int i = 1;i<=27;i++)
    {
        if(pos[i]<=27 && pos[i]>=19)
        {
            pos[i]=((pos[i]-18)*3)%10 + 18;
            a[i].push_back(make_pair(-90,'z'));
            v[i].push_back(make_pair(0,'z'));
        }
        //cout<<i<<" "<<pos[i]<<endl;
    }






}
int cn = 100;
while(cn--)
    display();

}
void reverseit()
{
    int sz = steps.size();
    for(int i = sz-1;i>=0;i--)
    {
        reverseface(steps[i]);
    }
}

void windowKey(unsigned char key,int x,int y)
{
  /*  Exit on ESC */
  if (key == 27) exit(0);
  else if (key == 'a' || key == 'A') toggleAxes = 1-toggleAxes;
  else if (key == 'v' || key == 'V') toggleValues = 1-toggleValues;
  else if (key == 'm' || key == 'M') toggleMode = 1-toggleMode;
  /*  Change field of view angle */
  else if (key == '-' && key>1) fov--;
  else if (key == '+' && key<179) fov++;
  /*  Change dimensions */
  else if (key == 'D') dim += 0.1;
  else if (key == 'd' && dim>1) dim -= 0.1;
else if(key == '6')
{
 steps.push_back('r');
    int marked[28] = {0};
    for(int i = 1;i<= 27;i++)
    {
        if(pos[i]%3 == 0)
            {a[i].push_back(make_pair(90,'x'));
                    v[i].push_back(make_pair(0,'x'));}

    }

    for(int i = 1;i<=27;i++)
    {
        if(pos[i]%3 == 0 )
        {
            pos[i]=(3*pos[i])%30;
        }
    }


}
else if(key == '4')
{
     steps.push_back('l');

    int marked[28] = {0};
    for(int i = 1;i<= 27;i++)
    {
        if(pos[i]%3 == 1)
       {

        a[i].push_back(make_pair(90,'x'));
                v[i].push_back(make_pair(0,'x'));
    }

    }

    for(int i = 1;i<=27;i++)
    {
        if(pos[i]%3 == 1)
        {
            pos[i]=(3*pos[i]+4)%30;
        }
        cout<<i<<" "<<pos[i]<<endl;
    }


}
else if(key == '5')
{
         steps.push_back('f');

    int marked[28] = {0};
    for(int i = 1;i<= 27;i++)
    {
        if(pos[i]<=9)
        {

            a[i].push_back(make_pair(90,'z'));
            v[i].push_back(make_pair(0,'z'));
        }


     }

    for(int i = 1;i<=27;i++)
    {
        if(pos[i]<=9)
        {
            pos[i]=(7*pos[i])%10;
        }
        cout<<i<<" "<<pos[i]<<endl;
    }



}
else if (key == '2')
{
             steps.push_back('d');

    int f = 0;
    for(int i = 1;i<= 27;i++)
    {
        f = 0;

        if(pos[i] == 7)
        {            f = 1;


            pos[i] = 9;

        }
         else if(pos[i] == 8)
        {
                        f = 1;

            pos[i] = 18;


        }
        else if(pos[i] == 9)
        {
            f = 1;

            pos[i] = 27;

        }
        else if(pos[i] == 16)
        {
            f = 1;

            pos[i] = 8;

        }
        else if(pos[i] == 17)
        {
                     f = 1;

            pos[i] = 17;

        }
        else if(pos[i] == 18)
        {
                        f = 1;

            pos[i] = 26;

        }
        else if(pos[i] == 25)
        {
                        f = 1;

            pos[i] = 7;

        }
        else if(pos[i] == 27)
        {
                        f = 1;

            pos[i] = 25;

        }
        else if(pos[i] == 26)
        {
            f = 1;
            pos[i] = 16;

        }
        if(f)
        {
             a[i].push_back(make_pair(90,'y'));
            v[i].push_back(make_pair(0,'y'));
        }


     }


}
else if (key == '8')
{
             steps.push_back('t');

    int f = 0;
    for(int i = 1;i<= 27;i++)
    {
        f = 0;

        if(pos[i] == 19)
        {            f = 1;


            pos[i] = 1;

        }
         else if(pos[i] == 10)
        {
                        f = 1;

            pos[i] = 2;


        }
        else if(pos[i] == 1)
        {
            f = 1;

            pos[i] = 3;

        }
        else if(pos[i] == 2)
        {
            f = 1;

            pos[i] = 12;

        }
        else if(pos[i] == 3)
        {
                     f = 1;

            pos[i] = 21;

        }
        else if(pos[i] == 12)
        {
                        f = 1;

            pos[i] = 20;

        }
        else if(pos[i] == 21)
        {
                        f = 1;

            pos[i] = 19;

        }
        else if(pos[i] == 20)
        {
                        f = 1;

            pos[i] = 10;

        }
        else if(pos[i] == 11)
        {
            f = 1;
            pos[i] = 11;

        }
        if(f)
        {
             a[i].push_back(make_pair(90,'y'));
            v[i].push_back(make_pair(0,'y'));
        }


     }


}
else if (key == '0')
{
             steps.push_back('b');

    for(int i = 1;i<=27;i++)
    {
        if(pos[i]<=27 && pos[i]>=19)
        {
            pos[i]=((pos[i]-18)*7)%10 + 18;
            a[i].push_back(make_pair(90,'z'));
            v[i].push_back(make_pair(0,'z'));
        }
        //cout<<i<<" "<<pos[i]<<endl;
    }

}
else if (key == 'c')
{
    reverseit();
}
int f = 1;
for(int i = 1;i<=27;i++)
{
    if(pos[i] != i)
        f = 0;
}
if(f)
{
    com = 1;
    cout<<com<<endl;

}
  project();
  glutPostRedisplay();
}

/*
 *  windowSpecial()
 *  ------
 *  GLUT calls this routine when an arrow key is pressed
 */
void windowSpecial(int key,int x,int y)
{
  /*  Right arrow key - increase azimuth by 5 degrees */
  if (key == GLUT_KEY_RIGHT) th += 5;
  /*  Left arrow key - decrease azimuth by 5 degrees */
  else if (key == GLUT_KEY_LEFT) th -= 5;
  /*  Up arrow key - increase elevation by 5 degrees */
  else if (key == GLUT_KEY_UP) ph += 5;
  /*  Down arrow key - decrease elevation by 5 degrees */
  else if (key == GLUT_KEY_DOWN) ph -= 5;

  /*  Keep angles to +/-360 degrees */
  th %= 360;
  ph %= 360;

  project();
  glutPostRedisplay();
}

/*
 *  windowMenu
 *  ------
 *  Window menu is the same as the keyboard clicks
 */
void windowMenu(int value)
{
  windowKey((unsigned char)value, 0, 0);
}

/*
 *  main()
 *  ----
 *  Start up GLUT and tell it what to do
 */
 void mouse(int button, int state, int x, int y)
{
{

int i = 0;
		 float t;
		 if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN )
		 {
			 //movex=x;movey=y;
			 angle+=10;                                                       // create new explosion
			  newExplosion ();
		 }

}
}


int f = 1 ;
int main(int argc,char* argv[])
{
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowSize(windowWidth,windowHeight);
  glutCreateWindow(windowName);
if(f == 0)
  {
      glutDisplayFunc(display2);
  glutIdleFunc(idle);
  }
  else
  {
        glutDisplayFunc(display);
  glutIdleFunc(display);
  }
  glutReshapeFunc(reshape);
  glutKeyboardFunc(windowKey);
  glutSpecialFunc(windowSpecial);
glutMouseFunc(mouse);

  glutCreateMenu(windowMenu);
  glutAddMenuEntry("Toggle Axes [a]",'a');
  glutAddMenuEntry("Toggle Values [v]",'v');
  glutAddMenuEntry("Toggle Mode [m]",'m');
  glutAttachMenu(GLUT_RIGHT_BUTTON);

  glutMainLoop();
  return 0;
}

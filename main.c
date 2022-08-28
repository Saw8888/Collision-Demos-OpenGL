#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

#define or ||
#define and &&
#define pCharacter "%c \n"
#define pInteger "%d \n"
#define pFloat "%f \n"
#define pDouble "%lf \n"
#define pUnsighned "%u \n"
#define pString "%s \n"

/*
format string:| input type:
      %c	  | character
      %d	  | digit (integer)
      %f	  | float
      %lf	  | double
      %u	  | unsigned
      %s	  | string
*/

int width=1000; //Screen width
int height=500; //Screen height
int px=200; //Player pos x
int py=100; //Player pos y
float playerSpeed=10.0;

void drawRect(int tlx,int tly,int boxWidth,int boxHeight){
 glBegin(GL_POLYGON);
 glVertex2f(tlx,tly+boxHeight); //Bottom Left
 glVertex2f(tlx,tly); //Top Left
 glVertex2f(tlx+boxWidth,tly); //Top Right
 glVertex2f(tlx+boxWidth,tly+boxHeight); //Bottom Right
 glEnd();
}

void checkCollisionRect(x1, y1, w1, h1, x2, y2, w2, h2) {
    if(x1>x2+w2 or x1+w1<x2 or y1>y2+h2 or y1+h1<y2)
        glColor3f(0, 1, 0);
	else {
        glColor3f(1, 0, 0);
        if (x1 < x2) {       // player hit the left wall
            printf("Left\n");
            px -= 1;
        }
        if (x1+w1 > x2+w2) { // player hit the right wall
            printf("Right\n");
            px += 1;
        }
        if (y1 < y2) {       // player hit the top wall
        	printf("Top\n");
            py -= 1;
        }
        if (y1+h1 > y2+h2) { // player hit the bottom wall
        	printf("Bottom\n");
            py += 1;
        }
    }
}
  	
void drawSquare(px,py,size){
 glPointSize(size);
 glBegin(GL_POINTS);
 glVertex2i(px,py);
 glEnd();
}

void Buttons(unsigned char key,int x,int y){
 if(key=='a'){px-=playerSpeed;} 	
 if(key=='d'){px+=playerSpeed;} 
 if(key=='w'){py-=playerSpeed;}
 if(key=='s'){py+=playerSpeed;}
}               
 
void display(){
 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 //-----------------------Draw----------------------
 checkCollisionRect(px,py,10,10,200,200,100,100);
 drawRect(200,200,100,100); //rect
 drawRect(px,py,10,10); //player
 //-------------------------------------------------
 glutSwapBuffers();
 glutPostRedisplay();
}

void init(){
 glClearColor(0.3,0.3,0.3,0);
 gluOrtho2D(0,width,height,0);
}

void main(int argc, char** argv){ 
 glutInit(&argc, argv);
 glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
 glutInitWindowSize(width,height);
 glutCreateWindow("OpenGL");
 init();
 glutDisplayFunc(display);
 glutKeyboardFunc(Buttons);
 glutMainLoop();
}


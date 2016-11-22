#include <stdio.h>
#include <stdlib.h>
#include <GL/freeglut.h>
#include <iostream>
#include "Airplane.cpp"
#include "Ground.cpp"


const GLfloat pi = 3.14;

const GLdouble left = -10.0;
const GLdouble right = 10.0;
const GLdouble bottom = -10.0;
const GLdouble top = 10.0;
const GLdouble near1 = 10.0;
const GLdouble far1 = 100.0;

GLfloat scale = 1.0;

GLfloat rotatex = 0.0;
GLfloat rotatey = 0.0;

GLfloat translatex = 0.0;
GLfloat translatey = 0.0;

int button_state_left = GLUT_UP;
int button_state_right = GLUT_UP;

int button_x, button_y;

Airplane* airplane;
Ground* ground;




void MyInit()
{
	airplane = new Airplane("wood.bmp");
	ground = new Ground("wood.bmp");
}

void Display()
{
	glEnable(GL_TEXTURE_2D);
	glClearStencil(0);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(0, 0, -(near1 + far1) / 2);
	glRotatef(rotatex, 1.0, 0, 0);
	glRotatef(rotatey, 0, 1.0, 0);
	glTranslatef(translatex, translatey, 0.0);
	glScalef(scale, scale, scale);

	ground->Draw();

	airplane->Draw();

	glFlush();
	glutSwapBuffers();
}

void Reshape(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(left, right, bottom, top, near1, far1);
	glDrawBuffer(GL_BACK);
	Display();
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'e':
		//airplane->MorePower();
		ground->Forward();
		break;
	case 'f':
		//airplane->LessPower();
		ground->Backward();
		break;
	case 'w':
		//airplane->Up();
		ground->Up();
		break;
	case 's':
	//	airplane->Down();
		ground->Down();
		break;
	case 'a':
		//airplane->Left();
		ground->Left();
		break;
	case 'd':
		//airplane->Right();
		ground->Right();
		break;
	case '+':
		scale += 0.1;
		break;
	case '-':
		if (scale > 0.1)
			scale -= 0.1;
		break;
	default: break;
	}
	
	Reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
}

void MouseButton(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		button_state_left = state;
		if (state == GLUT_DOWN)
		{
			button_x = x;
			button_y = y;
		}
	}

	if (button == GLUT_RIGHT_BUTTON)
	{
		button_state_right = state;
		if (state == GLUT_DOWN)
		{
			button_x = x;
			button_y = y;
		}
	}
}

void Update(int value)
{
	glutPostRedisplay();
	glutTimerFunc(25, Update, 0);
}

void MouseMotion(int x, int y)
{
	if (button_state_left == GLUT_DOWN)
	{
		translatex += 1.1 * (right - left) / glutGet(GLUT_WINDOW_WIDTH) * (x - button_x);
		button_x = x;
		translatey += 1.1 * (top - bottom) / glutGet(GLUT_WINDOW_HEIGHT) * (button_y - y);
		button_y = y;
		glutPostRedisplay();
	}

	if (button_state_right == GLUT_DOWN)
	{
		rotatey += 2 * (right - left) / glutGet(GLUT_WINDOW_WIDTH) * (x - button_x);
		button_x = x;
		rotatex -= 2 * (top - bottom) / glutGet(GLUT_WINDOW_HEIGHT) * (button_y - y);
		button_y = y;
		glutPostRedisplay();
	}
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_STENCIL);
	glutInitWindowSize(700, 700);
	glutCreateWindow("Airplane");

	MyInit();
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(MouseButton);
	glutMotionFunc(MouseMotion);

	glutTimerFunc(25, Update, 0);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);

	glutMainLoop();
	return 0;
}

//#include "stdafx.h"
#include <windows.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <vector>
#include <iostream>
#include "Triangle.h"

using namespace std;

float posX = 100, posY = 100, posZ = 0;
float rotation = 0.0;
float deviation = 0.0;

void MyInit(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);//select clearing (background) color
	glViewport(0, 0, 0, 0);//poczatek u.ws. lewy górny róg
	glMatrixMode(GL_PROJECTION);//Nastepne 2 wiersze b•d• modyfikowa³y m. PROJECTION
	glLoadIdentity();//inicjalizacja
	gluOrtho2D(0.0, 200.0, 0.0, 200.0);
	glMatrixMode(GL_MODELVIEW); //Nast•pny wiersz b•dzie modyfikowa³ m. MODELVIEW
	glLoadIdentity();
}

void MyDisplay(void)
{
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT);

	float colors[6][4] = {
		{ 1,0,0,1 },
		{ 1,1,0,1 },
		{ 1,1,1,1 },
		{ 1,0,1,1 },
		{ 0,1,0,1 },
		{ 0,0,1,1 }
	};

	vector<vector<float>> points1;
	vector<vector<float>> points2;

	float a = 8;
	float sx = 0, sy = 0;

	for (auto i = 0, j = 3; i < 3; i++, j--)
	{
		for (auto k = 0; k < j; k++)
		{
			if (i == 2 || k == 2 || (k == 1 && i == 1))
			{
				points1.push_back({ sx + (a * i),sy + (a * k), a });
			}
			else
			{
				points2.push_back({ sx + (a * i),sy + (a * k), a });
			}
		}
	}

	for (auto l = 0; l <= 3; l++)
	{
		glPushMatrix();
		glTranslatef(posX, posY, posZ);
		glRotatef((3 * rotation) + (l * 90), 0.0f, 0.0f, 1.0f);
		for (auto i = 0; i < 3; i++)
		{
			Triangle(points1.at(i), colors[i]).Draw();
		}
		glPopMatrix();
		glPushMatrix();
		glTranslatef(posX, posY, posZ);
		glRotatef(-rotation + (l * 90), 0.0f, 0.0f, 1.0f);
		for (auto i = 0; i < 3; i++)
		{
			glTranslatef(deviation, deviation, posZ);
			Triangle(points2.at(i), colors[i + 3]).Draw();
		}
		glPopMatrix();
	}

	glutSwapBuffers();
	glFlush();
}

void MyKeyboard(unsigned char key, int x, int y)
{
	float move_unit = 1.0;
	float rotate_unit = 0.03;

	switch (key)
	{
	case 'a':
		cout << "rotate left" << endl;
		deviation += rotate_unit;
		rotation += move_unit;
		break;

	case 'd':
		cout << "rotate right" << endl;
		deviation -= rotate_unit;
		rotation -= move_unit;
		break;
	default: break;
	}

	glutPostRedisplay();
}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);//single buffer and RGBA
	glutInitWindowSize(700, 700);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Pooler22");
	MyInit();
	glutDisplayFunc(MyDisplay);
	glutKeyboardFunc(MyKeyboard);
	glutMainLoop();//enter main loop and process events
	return 0;
}

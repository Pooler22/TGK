#include <GL/freeglut.h>
//#include <GL/gl.h>
#include <vector>
#include "Triangle.cpp"

using namespace std;

GLfloat posX = 100, posY = 100, posZ = 0;
GLfloat rotation = 0.0;
GLfloat deviation = 0.0;

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

void Display(void)
{
	GLfloat colors[6][4] = {
		{ 1,0,0,1 },
		{ 1,1,0,1 },
		{ 1,1,1,1 },
		{ 1,0,1,1 },
		{ 0,1,0,1 },
		{ 0,0,1,1 }
	};
	vector<vector<GLfloat>> points1;
	GLfloat a = 8, sx = 0, sy = 0;
	GLdouble a1 = 3.0f, a2 = 90.0f;

	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT);

	for (auto i = 0, j = 3; i < 3; i++, j--)
	{
		for (auto k = 0; k < j; k++)
		{
			points1.push_back({ sx + (a * i),sy + (a * k), a });
		}
	}


	for (auto l = 0; l < 4; l++)
	{
		for (auto i = 0; i < 6; i++)
		{
			glPushMatrix();

			glTranslatef(posX, posY, posZ);

			glRotatef(rotation / a1 + (l * a2), 0.0f, 0.0f, 1.0f);

			glTranslatef(deviation, deviation, posZ);
			glTranslatef(points1.at(i)[0] + 4, points1.at(i)[1] + 4, posZ);
			glRotatef(-rotation, 0.0f, 0.0f, 1.0f);
			glTranslatef(-points1.at(i)[0] - 4, -points1.at(i)[1] - 4, posZ);

			Triangle(points1.at(i), colors[i]).Draw();

			glPopMatrix();
		}
	}

	glFlush();
	glutSwapBuffers();
}

void Keyboard(unsigned char key, int x, int y)
{
	auto move_unit = 3.0f;
	auto rotate_unit = 0.09f;

	switch (key)
	{
	case 'a':
		deviation += rotate_unit;
		rotation += move_unit;
		break;

	case 'd':
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
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(700, 700);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Pooler22 - triangles");

	MyInit(); // todo
	glutDisplayFunc(Display);
	glutKeyboardFunc(Keyboard);

	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);

	glutMainLoop();
	return 0;
}

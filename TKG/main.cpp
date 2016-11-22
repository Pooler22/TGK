#include <GL/freeglut.h>
#include <vector>
#include "Triangle.cpp"

GLfloat posX = 100, posY = 100, posZ = 0;
GLfloat rotation = 0, deviation = 0;

void MyInit(void)
{
	glClearColor(0, 0, 0, 0);
	glViewport(0, 0, 0, 0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, posX * 2, 0, posY * 2);
	glMatrixMode(GL_MODELVIEW);
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
	std::vector<std::vector<GLfloat>> triangles;
	GLfloat a = 8, sx = 0, sy = 0, a1 = 3, a2 = 90;
	auto trianglesRows = 3, trianglesCols = 3, quadrantsNumber = 4;

	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT);

	for (auto i = 0; i < trianglesRows; i++)
	{
		for (auto j = 0; j < trianglesCols - i; j++)
		{
			triangles.push_back({ sx + (a * i),sy + (a * j), a });
		}
	}
	for (auto l = 0; l < quadrantsNumber; l++)
	{
		for (auto k = 0; k < triangles.size(); k++)
		{
			glPushMatrix();

			glTranslatef(posX, posY, posZ);

			glRotatef(rotation / a1 + (l * a2), 0, 0, 1);

			glTranslatef(deviation, deviation, posZ);
			glTranslatef(triangles.at(k)[0] + 4, triangles.at(k)[1] + 4, posZ);
			glRotatef(-rotation, 0, 0, 1);
			glTranslatef(-triangles.at(k)[0] - 4, -triangles.at(k)[1] - 4, posZ);

			Triangle(triangles.at(k), colors[k]).Draw();

			glPopMatrix();
		}
	}

	glutSwapBuffers();
	glFlush();
}

void Keyboard(unsigned char key, int x, int y)
{
	GLfloat move_unit = 3, rotate_unit = 0.09;

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

	MyInit();
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
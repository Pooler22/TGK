#include <GL/freeglut.h>

#include "Cube.cpp"
#include "Spring.cpp"
#include "Sphere.cpp"
#include "Texturable.cpp"

static GLfloat move = 0.0f;

Sphere* sphere = nullptr;
Spring* spring = nullptr;
Cube* cube = nullptr;


void MyInit()
{
	sphere = new Sphere(0, -18, -25, 6, Texturable::LoadTexture("wood.bmp"));
	spring = new Spring(0, -10, -25, Texturable::LoadTexture("steel.bmp"));
	cube = new Cube(0, 16, -25, 5, Texturable::LoadTexture("wood.bmp"));
}

void Display()
{
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	sphere->Draw(move);
	spring->Draw(move);
	cube->Draw();

	glutSwapBuffers();
	glFlush();
}

void Keyboard(unsigned char key, int x, int y)
{
	move = 10;
}

void Reshape(int width, int height)
{
	glClearColor(0, 0, 0, 0);
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-10, 10, -10, 10, 5, 40);
	Display();
}

void Update(int value)
{
	static auto passed = false;
	static GLfloat inclination = 1.2f;
	const static GLfloat precison = 0.0001f;
	const static GLfloat inclinationStep = 0.0102f;
	const static GLfloat step = 0.1f;

	if (move > 0)
	{
		inclination -= step;
	}
	else
	{
		inclination += step;
	}

	if (abs(move) > precison || move == 0)
	{
		move += inclination;
	}
	else
	{
		move = 0;
	}

	if (move < 0 && passed == false)
	{
		inclination += inclinationStep;
		passed = true;
	}
	else if (move > 0 && passed == true)
	{
		inclination -= inclinationStep;
		passed = false;
	}

	glutPostRedisplay();
	glutTimerFunc(20, Update, 0);
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(700, 700);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Pooler22 - spring");

	MyInit();
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);

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

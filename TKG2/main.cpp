#include <GL/freeglut.h>
#include <iostream>
#include "Cube.cpp"
#include "Spring.cpp"
#include "Sphere.cpp"

static GLfloat move = 0.0f;
auto mode = false;

Sphere* sphere = nullptr;
Spring* spring = nullptr;
Cube* cube = nullptr;

GLuint LoadTexture(const char* filename)
{
	GLuint texture;
	int width, height, size;
	unsigned char* data;
	FILE* file;

	width = 256;
	height = 256;
	size = width * height * 3;

	fopen_s(&file, filename, "rb");
	if (file == nullptr) return 0;
	data = static_cast<unsigned char *>(malloc(size));
	fread(data, size, 1, file);
	fclose(file);

	for (auto i = 0; i < size; i += 3)
	{
		std::swap(data[i], data[i + 2]);
	}

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
	free(data);

	return texture;
}

void MyInit()
{
	sphere = new Sphere(0, -18, -25, 6, LoadTexture("wood.bmp"));
	spring = new Spring(0, -10, -25, LoadTexture("steel.bmp"));
	cube = new Cube(0, 16, -25, 5, LoadTexture("wood.bmp"));
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

void Keyboard(unsigned char key, int x, int y) {

	switch (key) {
	case 'a':
		mode = !mode;
	default: break;
	case 27:
		exit(0);
	}
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
	static auto inclination = 1.2f;
	static auto precison = 0.000001;
	static auto inclinationStep = 0.102f;
	static auto step = 0.1f;

	if (move > 0)
	{
		inclination -= step;
	}
	else
	{
		inclination += step;
	}

	if (move > precison || move < (-precison) || move == 0)
	{
		move += inclination;
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

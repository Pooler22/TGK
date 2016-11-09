//#include <GL/glew.h>
#include <GL/freeglut.h>
//#include <GL/glu.h>
//#include <GL/gl.h>
#include <iostream>
#include "Cube.cpp"

class Cube;
static GLfloat ruch = 0.0;
static GLfloat ruch2 = 0.0;

const GLfloat pi = 3.14;

const GLdouble left = -10.0;
const GLdouble right = 10.0;
const GLdouble bottom = -10.0;
const GLdouble top = 10.0;
const GLdouble near1 = 10.0;
const GLdouble far1 = 100.0;

GLfloat scale = 1.0;

static GLfloat rotatex = 0.0;
static GLfloat rotatey = 0.0;

GLfloat translatex = 0.0;
GLfloat translatey = 0.0;

int button_state_left = GLUT_UP;
int button_state_right = GLUT_UP;

int button_x, button_y;

GLfloat lightColor[] = {0.0f, 0.0f, 0.0f, 0.0f};

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


void DiaplayBlock()
{
	auto block = new Cube(5, 5, 5, 5);
	glPushMatrix();
	block->Draw();
	glPopMatrix();
}

void DiaplaySpring()
{
}

void DiaplaySphere()
{
}

void Display()
{
	static auto texture = LoadTexture("wood.bmp");
	static auto texture1 = LoadTexture("steel.bmp");
	static auto texture2 = LoadTexture("wood.bmp");

	glEnable(GL_TEXTURE_2D);
	auto sphere = gluNewQuadric();
	gluQuadricDrawStyle(sphere, GLU_FILL);
	gluQuadricTexture(sphere, texture);
	gluQuadricNormals(sphere, GLU_SMOOTH);

	glClearStencil(0);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	// wybór macierzy modelowania
	glMatrixMode(GL_MODELVIEW);

	// macierz modelowania = macierz jednostkowa
	glLoadIdentity();

	// przesunięcie układu współrzędnych obiektu do środka bryły odcinania
	glTranslatef(0, 0, -(near1 + far1) / 2);

	// obroty obiektu - klawisze kursora
	glRotatef(rotatex, 1.0, 0, 0);
	glRotatef(rotatey, 0, 1.0, 0);

	glRotatef(90, 0, 1.0, 0);

	// przesunięcie obiektu - ruch myszką
	glTranslatef(translatex, translatey, 0.0);

	// skalowanie obiektu - klawisze "+" i "-"
	glScalef(scale, scale, scale);

	// rysowanie obiektu

	// glowna kula
	glBindTexture(GL_TEXTURE_2D, texture2);
	//Todo: load texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glPushMatrix();
	//glDisable(GL_DEPTH_TEST);
	//glDisable(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_ONE, GL_ONE_MINUS_DST_COLOR);
	glTranslatef(0.0, -8.0 + ruch, 0.0);
	glRotatef(90, 1.0, 0.0, 0.0);
	gluSphere(sphere, 6.0, 10, 10);
	//glDisable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, texture1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glPushMatrix();
	GLfloat delta = 0.1;
	GLfloat w_przesun;

	// zawsze licz wspolczynnik dla wartosci ruchu , ktory jest wartoscia bezwzgledna
	// w_przesun to krok z jakim przesunieciem
	if (ruch >= 0)
	{
		w_przesun = ruch / ((10 * pi) / delta);
	}
	else
	{
		w_przesun = ((-1) * ruch) / ((10 * pi) / delta);
	}
	ruch2 = ruch;

	//GLfloat w_przesuniecia = ruch/(10*pi);
	for (GLfloat t = 0; t < (10 * pi); t += delta)
	{
		GLfloat u = 0;
		glPushMatrix();
		glTranslatef(cos(t) * (3 + cos(u)), (0.6 * t + sin(u)) + (ruch2), sin(t) * (3 + cos(u)));
		gluSphere(sphere, 1.0, 20, 10);
		glPopMatrix();

		glPushMatrix();
		if (t < pi)
		{
			glTranslatef(0, (-t) + ruch, 0);
			gluSphere(sphere, 1.0, 20, 10);
		}
		glPopMatrix();

		glPushMatrix();
		if (t < 1.2 * pi)
		{
			glTranslatef(t, ruch, 0);
			gluSphere(sphere, 1.0, 20, 10);
		}
		glPopMatrix();

		glPushMatrix();
		if (t < (1.3 * pi))
		{
			glTranslatef(t, 18.9, 0);
			gluSphere(sphere, 1.0, 20, 10);
		}
		glPopMatrix();

		glPushMatrix();
		if (t > (6 * pi) && t < (7 * pi))
		{
			glTranslatef(0, t, 0);
			gluSphere(sphere, 1.0, 20, 10);
		}
		glPopMatrix();

		// sprezanie
		if (ruch > 0)
			ruch2 = ruch2 - w_przesun;
		// rozprezanie
		else if (ruch < 0)
			ruch2 = ruch2 + w_przesun;
	};
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lightColor);

	DiaplayBlock();

	glPushMatrix();
	//glDisable(GL_DEPTH_TEST);
	glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_EQUAL, 1, 1);
	// Make the stencil buffer not change
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE_MINUS_DST_COLOR);
	glTranslatef(0.0, -8.0 + ruch, 0.0);
	glRotatef(90, 1.0, 0.0, 0.0);
	gluSphere(sphere, 5.0, 40, 40);
	glDisable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	//glEnable(GL_DEPTH_TEST);
	glDisable(GL_STENCIL_TEST);
	glPopMatrix();

	glutSwapBuffers();
	glFlush();
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

void Update(int value)
{
	static auto wychylenie = 1.2f;
	static auto przeszedl = false;

	if (ruch > 0)
		wychylenie -= 0.1f;
	else
		wychylenie += 0.1f;

	if (ruch > 0.0001 || ruch < (-0.000001) || ruch == 0)
		ruch += wychylenie;

	if (ruch < 0 && przeszedl == false)
	{
		wychylenie += 0.102f;
		przeszedl = true;
	}
	else if (ruch > 0 && przeszedl == true)
	{
		wychylenie -= 0.102f;
		przeszedl = false;
	}

	glutPostRedisplay();
	glutTimerFunc(25, Update, 0);
}


int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(700, 700);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Pooler22 - spring");

	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
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

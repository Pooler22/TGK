#include <gl/freeglut.h>
#include <glm/glm.hpp>
#include "AirPlane.h"
#include "DrawString.h"

#define ADDR(i,j,k) (3*((j)*res + (i)) + (k))
#define DEGREE 60

bool upKey = false;
bool downKey = false;
bool leftKey = false;
bool rightKey = false;
bool showHelp = true;

bool isDay = true;
int res = 513;
float sealevel;

GLfloat* verts = nullptr;
GLfloat* norms = nullptr;
GLuint* faces = nullptr;

AirPlane ap;
DrawString ds;

float randomize(float x, float y)
{
	static auto a = 1688135690, b = 11176901;
	srand(((int(x) * a) % b) - ((int(y) * b) % a));
	return 2.0 * (float(rand()) / float(RAND_MAX)) - 1.0;
}

void mountain(int i, int j, int s)
{
	if (s > 1)
	{
		auto x0 = glm::vec3(verts[ADDR(i,j,0)], verts[ADDR(i,j,1)], verts[ADDR(i,j,2)]);
		auto x1 = glm::vec3(verts[ADDR(i+s,j,0)], verts[ADDR(i+s,j,1)], verts[ADDR(i+s,j,2)]);
		auto x2 = glm::vec3(verts[ADDR(i,j+s,0)], verts[ADDR(i,j+s,1)], verts[ADDR(i,j+s,2)]);
		auto x3 = glm::vec3(verts[ADDR(i+s,j+s,0)], verts[ADDR(i+s,j+s,1)], verts[ADDR(i+s,j+s,2)]);

		auto x01 = 0.5f * (x0 + x1);
		auto x02 = 0.5f * (x0 + x2);
		auto x13 = 0.5f * (x1 + x3);
		auto x23 = 0.5f * (x2 + x3);
		auto x0123 = 0.25f * (x0 + x1 + x2 + x3);

		x01.z += 0.5 * (float(s) / res) * randomize(x01.x, x01.y);
		x02.z += 0.5 * (float(s) / res) * randomize(x02.x, x02.y);
		x13.z += 0.5 * (float(s) / res) * randomize(x13.x, x13.y);
		x23.z += 0.5 * (float(s) / res) * randomize(x23.x, x23.y);
		x0123.z += 0.5 * (float(s) / res) * randomize(x0123.x, x0123.y);

		verts[ADDR(i+s/2,j,0)] = x01.x;
		verts[ADDR(i+s/2,j,1)] = x01.y;
		verts[ADDR(i+s/2,j,2)] = x01.z;

		verts[ADDR(i,j+s/2,0)] = x02.x;
		verts[ADDR(i,j+s/2,1)] = x02.y;
		verts[ADDR(i,j+s/2,2)] = x02.z;

		verts[ADDR(i+s,j+s/2,0)] = x13.x;
		verts[ADDR(i+s,j+s/2,1)] = x13.y;
		verts[ADDR(i+s,j+s/2,2)] = x13.z;

		verts[ADDR(i+s/2,j+s,0)] = x23.x;
		verts[ADDR(i+s/2,j+s,1)] = x23.y;
		verts[ADDR(i+s/2,j+s,2)] = x23.z;

		verts[ADDR(i+s/2,j+s/2,0)] = x0123.x;
		verts[ADDR(i+s/2,j+s/2,1)] = x0123.y;
		verts[ADDR(i+s/2,j+s/2,2)] = x0123.z;

		mountain(i, j, s / 2);
		mountain(i + s / 2, j, s / 2);
		mountain(i, j + s / 2, s / 2);
		mountain(i + s / 2, j + s / 2, s / 2);
	}
	else
	{
		float dx, dy, dz;

		if (i == 0)
		{
			dx = verts[ADDR(i+1,j,2)] - verts[ADDR(i,j,2)];
		}
		else if (i == res - 1)
		{
			dx = verts[ADDR(i,j,2)] - verts[ADDR(i-1,j,2)];
		}
		else
		{
			dx = (verts[ADDR(i+1,j,2)] - verts[ADDR(i-1,j,2)]) / 2.0;
		}

		if (j == 0)
		{
			dy = verts[ADDR(i,j+1,2)] - verts[ADDR(i,j,2)];
		}
		else if (j == res - 1)
		{
			dy = verts[ADDR(i,j,2)] - verts[ADDR(i,j-1,2)];
		}
		else
		{
			dy = (verts[ADDR(i,j+1,2)] - verts[ADDR(i,j-1,2)]) / 2.0;
		}

		dx *= res;
		dy *= res;
		dz = 1.0 / sqrt(dx * dx + dy * dy + 1.0);
		dx *= dz;
		dy *= dz;

		norms[ADDR(i,j,0)] = dx;
		norms[ADDR(i,j,1)] = dy;
		norms[ADDR(i,j,2)] = dz;
	}
}

void makemountain()
{
	int i, j;

	if (verts) free(verts);
	if (norms) free(norms);
	if (faces) free(faces);

	verts = static_cast<GLfloat *>(malloc(res * res * 3 * sizeof(GLfloat)));
	norms = static_cast<GLfloat *>(malloc(res * res * 3 * sizeof(GLfloat)));
	faces = static_cast<GLuint *>(malloc((res - 1) * (res - 1) * 6 * sizeof(GLuint)));

	verts[ADDR(0,0,0)] = -5.0;
	verts[ADDR(0,0,1)] = -5.0;
	verts[ADDR(0,0,2)] = 0.0;

	verts[ADDR(res-1,0,0)] = 5.0;
	verts[ADDR(res-1,0,1)] = -5.0;
	verts[ADDR(res-1,0,2)] = 0.0;

	verts[ADDR(0,res-1,0)] = -5.0;
	verts[ADDR(0,res-1,1)] = 5.0;
	verts[ADDR(0,res-1,2)] = 0.0;

	verts[ADDR(res-1,res-1,0)] = 5.0;
	verts[ADDR(res-1,res-1,1)] = 5.0;
	verts[ADDR(res-1,res-1,2)] = 0.0;

	mountain(0, 0, res - 1);

	auto f = faces;
	for (j = 0; j < res - 1; j++)
	{
		for (i = 0; i < res - 1; i++)
		{
			*f++ = j * res + i;
			*f++ = j * res + i + 1;
			*f++ = (j + 1) * res + i + 1;
			*f++ = j * res + i;
			*f++ = (j + 1) * res + i + 1;
			*f++ = (j + 1) * res + i;
		}
	}
}

void init(void)
{
	GLfloat amb[] = {0.2,0.2,0.2};
	GLfloat diff[] = {1.0,1.0,1.0};
	GLfloat spec[] = {1.0,1.0,1.0};

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diff);
	glLightfv(GL_LIGHT0, GL_SPECULAR, spec);

	glClearColor(0.5, 0.5, 1.0, 0.0); // sky

	glEnable(GL_DEPTH_TEST);

	sealevel = -0.2;

	makemountain();
}

void drawStrings()
{
	glColor3d(0.2, 0.2, 0.2);
	ds.draw("  h   key to show/hide help", GLUT_WINDOW_WIDTH, GLUT_WINDOW_HEIGHT, 1, 5);
	if (showHelp)
	{
		ds.draw("  UP  key to pitch down", GLUT_WINDOW_WIDTH, GLUT_WINDOW_HEIGHT, 1, 10);
		ds.draw(" Down key to pitch up", GLUT_WINDOW_WIDTH, GLUT_WINDOW_HEIGHT, 1, 14);
		ds.draw(" Left key to roll left", GLUT_WINDOW_WIDTH, GLUT_WINDOW_HEIGHT, 1, 18);
		ds.draw("Right key to roll right", GLUT_WINDOW_WIDTH, GLUT_WINDOW_HEIGHT, 1, 22);
		ds.draw("  +   key to sealevel up", GLUT_WINDOW_WIDTH, GLUT_WINDOW_HEIGHT, 1, 26);
		ds.draw("  -   key to sealevel down", GLUT_WINDOW_WIDTH, GLUT_WINDOW_HEIGHT, 1, 30);
		ds.draw("  f   key to resolution up", GLUT_WINDOW_WIDTH, GLUT_WINDOW_HEIGHT, 1, 34);
		ds.draw("  c   key to resolution down", GLUT_WINDOW_WIDTH, GLUT_WINDOW_HEIGHT, 1, 38);
		ds.draw("Space key to shoot a bullet", GLUT_WINDOW_WIDTH, GLUT_WINDOW_HEIGHT, 1, 42);
	}
}

void keyboardFlag()
{
	if (leftKey)
	{
		ap.updateRoll(DEGREE);
	}
	if (rightKey)
	{
		ap.updateRoll(-DEGREE);
	}
	if (upKey)
	{
		ap.updatePitch(-DEGREE);
	}
	if (downKey)
	{
		ap.updatePitch(DEGREE);
	}
}

void display(void)
{
	if (isDay)
	{
		glClearColor(0.5, 0.5, 1.0, 0.0);
	}
	else
	{
		glClearColor(0.1, 0.1, 0.2, 0.1);
	}

	GLfloat tanamb[] = {0.2,0.15,0.1,1.0};
	GLfloat tandiff[] = {0.4,0.3,0.2,1.0};
	GLfloat tanspec[] = {0.0,0.0,0.0,1.0}; // dirt doesn't glisten

	GLfloat seaamb[] = {0.0,0.0,0.2,1.0};
	GLfloat seadiff[] = {0.0,0.0,0.8,1.0};
	GLfloat seaspec[] = {0.5,0.5,1.0,1.0}; // Single polygon, will only have highlight if light hits a vertex just right

	GLfloat lpos[] = {0.0,0.0,10.0,0.0}; // sun, high noon


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	glLoadIdentity();

	keyboardFlag();
	ap.moveForward();
	ap.updateCamera();
//	ap.drawPlain();
	drawStrings();

	// send the light position down as if it was a vertex in world coordinates
	glLightfv(GL_LIGHT0, GL_POSITION, lpos);

	// load terrain material
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, tanamb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, tandiff);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, tanspec);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 50.0);

	// Send terrain mesh through pipeline
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glVertexPointer(3,GL_FLOAT, 0, verts);
	glNormalPointer(GL_FLOAT, 0, norms);
	glDrawElements(GL_TRIANGLES, 6 * (res - 1) * (res - 1), GL_UNSIGNED_INT, faces);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);

	// load water material
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, seaamb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, seadiff);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, seaspec);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 10.0);

	// Send water as a single quad
	glNormal3f(0.0, 0.0, 1.0);
	glBegin(GL_QUADS);
	glVertex3f(-5, -5, sealevel);
	glVertex3f(5, -5, sealevel);
	glVertex3f(5, 5, sealevel);
	glVertex3f(-5, 5, sealevel);
	glEnd();

	ap.drawBullet();

	glutSwapBuffers();
	glFlush();
	glutPostRedisplay();
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0, float(w) / h, 0.01, 10.0);
	glMatrixMode(GL_MODELVIEW);
}

void arrowkeys(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
		leftKey = true;
		break;
	case GLUT_KEY_RIGHT:
		rightKey = true;
		break;
	case GLUT_KEY_UP:
		upKey = true;
		break;
	case GLUT_KEY_DOWN:
		downKey = true;
		break;
	default: break;
	}
}

void allowkeysup(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
		leftKey = false;
		break;
	case GLUT_KEY_RIGHT:
		rightKey = false;
		break;
	case GLUT_KEY_UP:
		upKey = false;
		break;
	case GLUT_KEY_DOWN:
		downKey = false;
		break;
	default: break;
	}
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case '-':
		sealevel -= 0.01;
		break;
	case '+':
	case '=':
		sealevel += 0.01;
		break;
	case 'f':
		res = (res - 1) * 2 + 1;
		makemountain();
		break;
	case 'c':
		res = (res - 1) / 2 + 1;
		makemountain();
		break;
	case 'h':
		showHelp = !showHelp;
		break;
	case ' ':
		ap.shootBullet();
		break;
	case 'd':
		isDay = !isDay;
		break;
	case 27:
		exit(0);
	default: break;
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1280, 720);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Airplane");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(arrowkeys);
	glutSpecialUpFunc(allowkeysup);
	glutMainLoop();
	return 0;
}

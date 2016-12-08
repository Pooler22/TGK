#include <gl/freeglut.h>
#include <glm/glm.hpp>
#include "AirPlane.h"
#include "Menu.h"
#include "Mountain.h"
#include <ctime>
#include "ParticleSystem.h"
#include <iostream>

bool upKey = false;
bool downKey = false;
bool leftKey = false;
bool rightKey = false;
bool isDay = true;


int button_state_left = GLUT_UP;
int button_state_right = GLUT_UP;
int button_x;
int button_y;
GLfloat scale = 1.0f;
GLfloat rotatex = 0.0f;
GLfloat rotatey = 0.0f;
GLfloat rotatez = 0.0f;
GLfloat translatex = 0.0f;
GLfloat translatey = 0.0f;
GLfloat translatez = 0.0f;
GLfloat movex = 0.0f;
GLfloat movey = 0.0f;
GLfloat movez = 0.0f;

GLfloat sealevel;

AirPlane ap = AirPlane(Texturable::LoadTexture("steel.bmp"));
Menu menu;
Mountain mountain;
ParticleSystem ps;


void init(void)
{
	sealevel = -0.2f;

	GLfloat amb[] = {0.2f,0.2f,0.2f};
	GLfloat diff[] = {1.0f,1.0f,1.0f};
	GLfloat spec[] = {1.0f,1.0f,1.0f};

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diff);
	glLightfv(GL_LIGHT0, GL_SPECULAR, spec);


	glEnable(GL_DEPTH_TEST);

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);

	menu = Menu();
	mountain = Mountain();
	mountain.makemountain();

	ps.init();
}

void keyboardFlag()
{
	const auto deegre = 90.f;
	if (leftKey)
	{
		ap.updateRoll(-deegre);
	}
	if (rightKey)
	{
		ap.updateRoll(deegre);
	}
	if (upKey)
	{
		ap.updatePitch(-deegre);
	}
	if (downKey)
	{
		ap.updatePitch(deegre);
	}
}

void display(void)
{
	GLfloat* a;

	glEnable(GL_FOG); // włączenie efektu mgły
	glHint(GL_FOG_HINT, GL_DONT_CARE); // wskazówki jakości generacji mgły
	if (isDay)
	{
		glFogfv(GL_FOG_COLOR, new float[4]{1,1,1,1}); // kolor mgły
	}
	else
	{
		glFogfv(GL_FOG_COLOR, new float[4]{0,0,0,1}); // kolor mgły
	}

	glFogf(GL_FOG_DENSITY, 0.2f); // gęstość mgły
	glFogf(GL_FOG_MODE, GL_EXP2); // rodzaj mgły
	glFogf(GL_FOG_START, 1.0f); // początek i koniec oddziaływania mgły liniowej
	glFogf(GL_FOG_END, 2.0f);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	if (isDay)
	{
		GLfloat amb[] = {0.2f,0.2f,0.2f};
		GLfloat diff[] = {1.0f,1.0f,1.0f};
		GLfloat spec[] = {1.0f,1.0f,1.0f};

		glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, diff);
		glLightfv(GL_LIGHT0, GL_SPECULAR, spec);
		a = new GLfloat[4]{0.9f, 0.9f, 0.9f, 0.0f};
	}
	else
	{
		GLfloat amb[] = {0.2f,0.2f,0.1f};
		GLfloat diff[] = {1.0f,1.0f,0.1f};
		GLfloat spec[] = {1.0f,1.0f,0.1f};

		glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, diff);
		glLightfv(GL_LIGHT0, GL_SPECULAR, spec);
		a = new GLfloat[4]{0.0f, 0.0f, 0.0f, 0.1f};
	}

	// kolor tłaglClear
	glClearColor(a[0], a[1], a[2], a[3]);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);

	GLfloat tanamb[] = {0.2f,0.15f,0.1f,1.0f};
	GLfloat tandiff[] = {0.4f,0.3f,0.2f,1.0f};
	GLfloat tanspec[] = {0.0f,0.0f,0.0f,1.0f}; // dirt doesn't glisten

	GLfloat seaamb[] = {0.0f,0.0f,0.2f,1.0f};
	GLfloat seadiff[] = {0.0f,0.0f,0.8f,1.0f};
	GLfloat seaspec[] = {0.5f,0.5f,1.0f,1.0f}; // Single polygon, will only have highlight if light hits a vertex just right

	GLfloat lpos[] = {0.0f,0.0f,10.0f,0.0f}; // sun

	glLoadIdentity();

	keyboardFlag();

	glRotatef(rotatex, 1.0, 0, 0);
	glRotatef(rotatey, 0, 1.0, 0);
	glTranslatef(translatex, translatey, 0.0);
	
	glScalef(scale, scale, scale);
	glTranslatef(-movex, -movey, -movez);

	ps.draw();
	ap.drawPlain();
	ap.moveForward(sealevel);
	ap.updateCamera();
	menu.drawStrings();

	glTranslatef(movex, movey, -movez);

	// send the light position down as if it was a vertex in world coordinates
	glLightfv(GL_LIGHT0, GL_POSITION, lpos);

	glShadeModel(GL_FLAT);

	// load terrain material
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, tanamb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, tandiff);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, tanspec);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 50.0);

	// Send terrain mesh through pipeline
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glVertexPointer(3,GL_FLOAT, 0, mountain.verts);
	glNormalPointer(GL_FLOAT, 0, mountain.norms);
	glDrawElements(GL_TRIANGLES, 6 * (mountain.res - 1) * (mountain.res - 1), GL_UNSIGNED_INT, mountain.faces);
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
	glutPostRedisplay();
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.f, float(w) / h, 0.01f, 10.f);
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
	case 'z':
		ap.increaseSpeed();
		break;
	case 'x':
		ap.decreaseSpeed();
		break;

	case '-':
		scale -= 0.1f;
		break;
	case '+':
	case '=':
		scale += 0.1f;
		break;
	case '}':
	case ']':
		sealevel -= 0.01f;
		break;
	case '{':
	case '[':
		sealevel += 0.01f;
		break;
	case 'h':
		menu.changeVisibilityMenu();
		break;
	case ' ':
		ap.shootBullet();
		break;
	case 'd':
		isDay = !isDay;
		break;
	case '8':
		movey -= 0.1f;
		break;
	case '2':
		movey += 0.1f;
		break;
	case '4':
		movez -= 0.1f;
		break;
	case '6':
		movez += 0.1f;
		break;
	case '9':
		movex -= 0.1f;
		break;
	case '3':
		movex += 0.1f;
		break;
	case '0':
		movex = movey = movez = 0.0f;
		translatex = translatey = translatez = 0.0f;
		rotatex = rotatey = rotatez = 0.0f;
		scale = 1.0f;
		break;
	case 27:
		exit(0);
	default: break;
	}
}

void mousemotion(int x, int y)
{
	if (button_state_left == GLUT_DOWN)
	{
		translatex += 0.8f/ glutGet(GLUT_WINDOW_WIDTH) * (x - button_x);
		button_x = x;
		translatey += 0.8f/ glutGet(GLUT_WINDOW_HEIGHT) * (button_y - y);
		button_y = y;
	}
	if (button_state_right == GLUT_DOWN)
	{
		rotatey += 40.f/ glutGet(GLUT_WINDOW_WIDTH) * (x - button_x);
		button_x = x;
		rotatex -= 40.f/ glutGet(GLUT_WINDOW_HEIGHT) * (button_y - y);
		button_y = y;
	}
	glutPostRedisplay();
}

void mousebutton(int button, int state, int x, int y)
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
	glutMouseFunc(mousebutton);
	glutMotionFunc(mousemotion);
	glutMainLoop();
	return 0;
}

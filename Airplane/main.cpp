﻿#include <gl/freeglut.h>
#include <glm/glm.hpp>
#include "AirPlane.h"
#include "DrawString.h"
#include "Menu.h"
#include "Mountain.h"
#include <ctime>
#include "System.h"

bool upKey = false;
bool downKey = false;
bool leftKey = false;
bool rightKey = false;
bool isDay = true;

GLfloat sealevel;
GLfloat texture_t[10];

AirPlane ap = AirPlane(Texturable::LoadTexture("steel.bmp"));
Menu menu;
Mountain mountain;
System particleSystem;


void drawParticles(void)
{
	glScalef(0.1, 0.1, 0.1);
	glRotatef(90, 1, 0, 0);
	glTranslatef(0, 5, 4);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(0.4, 0.0, 0.0);
	for (auto i = 1; i < particleSystem.getNumOfParticles(); i++)
	{
		glPushMatrix();

		// set color and fade value (alpha) of current particle
		glColor4f(particleSystem.getR(i), particleSystem.getG(i), particleSystem.getB(i), particleSystem.getAlpha(i));
		// move the current particle to its new position
		glTranslatef(particleSystem.getXPos(i), particleSystem.getYPos(i), particleSystem.getZPos(i)); //+ zoom
		// rotate the particle (this is proof of concept for when proper smoke texture_t is added)
		glRotatef(particleSystem.getDirection(i) - 0, 0, 0, 1);
		// scale the wurrent particle (only used for smoke)
		glScalef(particleSystem.getScale(i), particleSystem.getScale(i), particleSystem.getScale(i));

		//glDisable(GL_DEPTH_TEST);
		//glEnable(GL_BLEND);

		//glBlendFunc(GL_DST_COLOR, GL_ZERO);
		glBindTexture(GL_TEXTURE_2D, texture_t[0]);

		glBegin(GL_QUADS);
		glTexCoord2d(0, 0);
		glVertex3f(-0.1, -0.1, 0);
		glTexCoord2d(0.1, 0);
		glVertex3f(0.1, -0.1, 0);
		glTexCoord2d(0.1, 0.1);
		glVertex3f(0.1, 0.1, 0);
		glTexCoord2d(0, 0.1);
		glVertex3f(-0.1, 0.1, 0);
		glEnd();

		//glBlendFunc(GL_ONE, GL_ONE);
		glBindTexture(GL_TEXTURE_2D, texture_t[1]);

		glBegin(GL_QUADS);
		glTexCoord2d(0, 0);
		glVertex3f(-0.1, -0.1, 0);
		glTexCoord2d(0.1, 0);
		glVertex3f(0.1, -0.1, 0);
		glTexCoord2d(0.1, 0.1);
		glVertex3f(0.1, 0.1, 0);
		glTexCoord2d(0, 0.1);
		glVertex3f(-0.1, 0.1, 0);
		glEnd();

		//glEnable(GL_DEPTH_TEST);

		glPopMatrix();
	}
}

void init(void)
{
	sealevel = -0.2;
	GLfloat amb[] = {0.2f,0.2f,0.2f};
	GLfloat diff[] = {1.0f,1.0f,1.0f};
	GLfloat spec[] = {1.0f,1.0f,1.0f};

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diff);
	glLightfv(GL_LIGHT0, GL_SPECULAR, spec);

	glClearColor(0.5, 0.5, 1.0, 0.0); // sky

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);


	menu = Menu();
	mountain = Mountain();
	mountain.makemountain();

	//texture_t[0] = LoadTextureRAW("particle_mask.raw", 256, 256); //load alpha for texture_t
	//texture_t[1] = LoadTextureRAW("particle.raw", 256, 256); //load texture_t

	particleSystem.setSystemType(4);
	particleSystem.createParticles();
}

void keyboardFlag()
{
	const auto deegre = 90;
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
	glClearDepth(1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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

	glFogf(GL_FOG_DENSITY, 0.2); // gęstość mgły
	glFogf(GL_FOG_MODE, GL_EXP2); // rodzaj mgły
	glFogf(GL_FOG_START, 1.0); // początek i koniec oddziaływania mgły liniowej
	glFogf(GL_FOG_END, 2.0);

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

		glClearColor(0.9, 0.9, 0.9, 0.0);
	}
	else
	{
		GLfloat amb[] = {0.2f,0.2f,0.1f};
		GLfloat diff[] = {1.0f,1.0f,0.1f};
		GLfloat spec[] = {1.0f,1.0f,0.1f};

		glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, diff);
		glLightfv(GL_LIGHT0, GL_SPECULAR, spec);

		glClearColor(0.0, 0.0, 0.0, 0.1);
	}
	glEnable(GL_DEPTH_TEST);

	GLfloat tanamb[] = {0.2,0.15,0.1,1.0};
	GLfloat tandiff[] = {0.4,0.3,0.2,1.0};
	GLfloat tanspec[] = {0.0,0.0,0.0,1.0}; // dirt doesn't glisten

	GLfloat seaamb[] = {0.0,0.0,0.2,1.0};
	GLfloat seadiff[] = {0.0,0.0,0.8,1.0};
	GLfloat seaspec[] = {0.5,0.5,1.0,1.0}; // Single polygon, will only have highlight if light hits a vertex just right

	GLfloat lpos[] = {0.0,0.0,10.0,0.0}; // sun

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	glLoadIdentity();

	keyboardFlag();


	///////////////

	glPushMatrix();
	particleSystem.updateParticles();
	drawParticles();
	glPopMatrix();

	//////////////////

	ap.drawPlain();
	ap.moveForward(sealevel);
	ap.updateCamera();
	menu.drawStrings();

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
	glFlush();
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
		sealevel -= 0.01;
		break;
	case '+':
	case '=':
		sealevel += 0.01;
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

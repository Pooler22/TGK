#pragma once
#include <GL/freeglut.h>
#include <iostream>
#include "Texturable.cpp"
#define PI 3.14159265358979323846

class Spring : public Texturable
{
public:
	explicit Spring::Spring(GLfloat x, GLfloat y, GLfloat z, GLuint texture) : Texturable(texture), w_move(0), x(x), y(y), z(z)
	{
		glEnable(GL_TEXTURE_2D);
		sphereObject = gluNewQuadric();
		gluQuadricDrawStyle(sphereObject, GLU_FILL);
		gluQuadricTexture(sphereObject, texture);
		gluQuadricNormals(sphereObject, GLU_SMOOTH);
	}

	void Spring::Draw(GLfloat move)
	{
		static auto delta = 0.1f;

		Texturable::Draw();
		
		glPushMatrix();
		
		glTranslatef(x, y, z);
		glRotatef(90, 0, 1, 0);
		
		if (move >= 0)
		{
			w_move = move / (100 * PI);
		}
		else
		{
			w_move = -1 * move / (100 * PI);
		}
		GLfloat ruch2 = move;

		for (GLfloat t = 0; t < (10 * PI); t += delta)
		{
			GLfloat u = 0;
			glPushMatrix();
			glTranslatef(cos(t) * (3 + cos(u)), (0.6f * t + sin(u)) + (ruch2), sin(t) * (3 + cos(u)));
			gluSphere(sphereObject, 1, 20, 10);
			glPopMatrix();

			glPushMatrix();
			if (t < PI)
			{
				glTranslatef(0, (-t) + move, 0);
				gluSphere(sphereObject, 1, 20, 10);
			}
			glPopMatrix();

			glPushMatrix();
			if (t < 1.2 * PI)
			{
				glTranslatef(t, move, 0);
				gluSphere(sphereObject, 1, 20, 10);
			}
			glPopMatrix();

			glPushMatrix();
			if (t < (1.3 * PI))
			{
				glTranslatef(t, 18.9f, 0);
				gluSphere(sphereObject, 1, 20, 10);
			}
			glPopMatrix();

			glPushMatrix();
			if (t > (6 * PI) && t < (7 * PI))
			{
				glTranslatef(0, t, 0);
				gluSphere(sphereObject, 1, 20, 10);
			}
			glPopMatrix();

			if (move > 0)
				ruch2 = ruch2 - w_move;
			else if (move < 0)
				ruch2 = ruch2 + w_move;
		};
		glPopMatrix();
	}

	GLUquadric* sphereObject;
	GLfloat x;
	GLfloat y;
	GLfloat z;
	
	
	GLfloat w_move;
};

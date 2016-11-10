#pragma once
#include <GL/freeglut.h>

class Spring
{
public:
	Spring::Spring(GLfloat x, GLfloat y, GLfloat z, GLfloat r, GLfloat n) : x(&x), y(&y), z(&z), r(&r), n(&n)
	{

	}

	void Spring::Draw() const
	{
		glBegin(GL_QUADS);

		glEnd();
	}

	GLfloat* x;
	GLfloat* y;
	GLfloat* z;
	GLfloat* r;
	GLfloat* n;
};
#pragma once
#include <GL/freeglut.h>

class Sphere
{
public:
	Sphere::Sphere(GLfloat x, GLfloat y, GLfloat z, GLfloat r, GLfloat n) : x(&x), y(&y), z(&z), r(&r), n(&n)
	{

	}

	void Sphere::Draw() const
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
#pragma once
#include <GL/freeglut.h>

class Point
{
public:
	Point::Point(GLfloat x, GLfloat y, GLfloat z): x(x), y(y), z(z)
	{
	}

	void Point::Draw() const
	{
		glVertex3f(x, y, z);
	}

	GLfloat x;
	GLfloat y;
	GLfloat z;
};

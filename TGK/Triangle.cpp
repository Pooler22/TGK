#pragma once
#include <GL/freeglut.h>
#include <vector>

class Triangle
{
public:
	Triangle::Triangle(std::vector<GLfloat> xyz, GLfloat* color)
	{
		this->a = new GLfloat[2]{xyz[0], xyz[1]};
		this->b = new GLfloat[2]{xyz[0] + xyz[2], xyz[1]};
		this->c = new GLfloat[2]{xyz[0], xyz[1] + xyz[2]};
		this->color = new GLfloat[4]{color[0], color[1],color[2], color[3]};
	}

	void Triangle::Draw() const
	{
		glBegin(GL_POLYGON);
		glColor4fv(this->color);
		glVertex2fv(this->a);
		glVertex2fv(this->b);
		glVertex2fv(this->c);
		glEnd();
	}

	GLfloat* a;
	GLfloat* b;
	GLfloat* c;
	GLfloat* color;
};

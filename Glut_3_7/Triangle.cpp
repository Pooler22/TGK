#pragma once
#include <windows.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <iostream>
#include <vector>

class Triangle
{
public:
	Triangle::Triangle(std::vector<GLfloat> abc, GLfloat* color1)
	{
		this->a = new GLfloat[2]{ abc[0], abc[1] };
		this->b = new GLfloat[2]{ abc[0] + abc[2], abc[1] };
		this->c = new GLfloat[2]{ abc[0], abc[1] + abc[2] };
		this->color = new GLfloat[4]{ color1[0], color1[1],color1[2], color1[3] };
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

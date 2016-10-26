#include <windows.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include "Triangle.h"

Triangle::Triangle(std::vector<float> abc, float* color1)
{
	this->a = new float[2]{ abc[0], abc[1] };
	this->b = new float[2]{ abc[0] + abc[2], abc[1] };
	this->c = new float[2]{ abc[0], abc[1] + abc[2] };
	this->color = new float[4]{ color1[0], color1[1],color1[2], color1[3] };
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

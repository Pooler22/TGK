#pragma once
#include <GL/freeglut.h>
#include <vector>
#include "Square.cpp"
#include <memory>

class Cube
{
public:
	Cube::Cube(GLfloat x, GLfloat y, GLfloat z, GLfloat n)
	{
//		squares(new std::vector<Square>);
		//squares->push_back(*new Square(5, 5, 5, 5));
		
	}

	void Cube::Draw() const
	{
		
		// lewa œciana
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(-5.0, -5.0, -5.0);
		glTexCoord2f(0.0, 1.0);
		glVertex3f(-5.0, -5.0, 5.0);
		glTexCoord2f(1.0, 1.0);
		glVertex3f(-5.0, 5.0, 5.0);
		glTexCoord2f(1.0, 0.0);
		glVertex3f(-5.0, 5.0, -5.0);
		glEnd();
		// tylna œciana
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(-5.0, -5.0, -5.0);
		glTexCoord2f(0.0, 1.0);
		glVertex3f(-5.0, 5.0, -5.0);
		glTexCoord2f(1.0, 1.0);
		glVertex3f(5.0, 5.0, -5.0);
		glTexCoord2f(1.0, 0.0);
		glVertex3f(5.0, -5.0, -5.0);
		glEnd();

		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(-5.0, -5.0, 5.0);
		glTexCoord2f(0.0, 1.0);
		glVertex3f(-5.0, 5.0, 5.0);
		glTexCoord2f(1.0, 1.0);
		glVertex3f(5.0, 5.0, 5.0);
		glTexCoord2f(1.0, 0.0);
		glVertex3f(5.0, -5.0, 5.0);
		glEnd();

		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(5.0, -5.0, -5.0);
		glTexCoord2f(0.0, 1.0);
		glVertex3f(5.0, -5.0, 5.0);
		glTexCoord2f(1.0, 1.0);
		glVertex3f(5.0, 5.0, 5.0);
		glTexCoord2f(1.0, 0.0);
		glVertex3f(5.0, 5.0, -5.0);
		glEnd();

		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(-5.0, 5.0, -5.0);
		glTexCoord2f(0.0, 1.0);
		glVertex3f(-5.0, 5.0, 5.0);
		glTexCoord2f(1.0, 1.0);
		glVertex3f(5.0, 5.0, 5.0);
		glTexCoord2f(1.0, 0.0);
		glVertex3f(5.0, 5.0, -5.0);
		glEnd();
	}

	std::unique_ptr<std::vector<Square>> squares;
};

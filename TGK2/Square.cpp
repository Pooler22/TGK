#pragma once
#include <GL/freeglut.h>

class Square
{
public:
	Square::Square(GLfloat x, GLfloat y, GLfloat z, GLfloat n) : x(&x), y(&y), z(&z), n(&n)
	{

	}

	void Square::Draw() const
	{
		glTranslatef(0.0, 26.5, 0.0);
		//podstawa
		glBegin(GL_QUADS);

		glTexCoord2f(0.0, 0.0);
		glVertex3f(-*x, -*y, -*z);

		glTexCoord2f(0.0, 1.0);
		glVertex3f(-*x, -*y, *z);

		glTexCoord2f(1.0, 1.0);
		glVertex3f(*x, -*y, *z);

		glTexCoord2f(1.0, 0.0);
		glVertex3f(*x, -*y, -*z);

		glEnd();
	}

	GLfloat* x;
	GLfloat* y;
	GLfloat* z;
	GLfloat* n;
};
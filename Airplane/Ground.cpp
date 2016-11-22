#pragma once
#include <gl/freeglut.h>
#include "Texturable.cpp"

class Ground :Texturable
{
public:
	explicit Ground(char* texture) : Texturable(texture)
	{
	}

	void Draw() const
	{
		Texturable::Draw();
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		//glRotatef(80, 1.0, 0, 0);
		
		glPushMatrix();

		glTranslatef(translateX, translateY, translateZ);
		glRotatef(rotateX, 1.0, 0, 0);
		glRotatef(rotateZ, 0, 0, 1.0);
		glRotatef(rotateY, 0, 1.0, 0);

		glBegin(GL_QUADS);

		glTexCoord2f(0.0, 0.0);
		glVertex3f(-1100.0, -35.0, -1000);
		glTexCoord2f(0.0, 1.0);
		glVertex3f(1100.0, -35.0, -1000);
		glTexCoord2f(1.0, 1.0);
		glVertex3f(1100.0, -35.0, 1000);
		glTexCoord2f(1.0, 0.0);
		glVertex3f(-1100.0, -35.0, 1000);

		glEnd();

		glPopMatrix();
	}

	void Left()
	{
		translateX++;
	}

	void Right()
	{
		translateX--;
	}

	void Up()
	{
		translateZ++;
	}
	void Down()
	{
		translateZ--;
	}

	void Forward()
	{
		translateY++;
		
	}
	void Backward()
	{
		translateY--;
	}
	GLfloat rotateX = 0.0;
	GLfloat rotateY = 0.0;
	GLfloat rotateZ = 0.0;
	GLfloat translateX = 0.0;
	GLfloat translateY = 0.0;
	GLfloat translateZ = 0.0;
};
#pragma once
#include <gl/freeglut.h>
#include "Texturable.cpp"

class Airplane:Texturable
{
public:
	explicit Airplane(char* texture): Texturable(texture)
	{
	}

	void Draw()
	{
		Texturable::Draw();
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glRotatef(270, 1.0, 0, 0);

		//translateX += step;
		//translateY += step;
		
		glTranslatef(translateX, translateY, translateZ);
		glRotatef(rotateX, 1.0, 0, 0);
		glRotatef(rotateZ, 0, 0, 1.0);
		glRotatef(rotateY, 0, 1.0, 0);

		glPushMatrix();

		glBegin(GL_POLYGON);

		glVertex3f(-11.0, -17.0, 0);
		glVertex3f(0, 15.0, 0);
		glVertex3f(11.0, -17.0, 0);

		glEnd();

		glPopMatrix();
	}

	void Up()
	{
		rotateX++;
	}

	void Down()
	{
		rotateX--;
	}

	void Left()
	{
		rotateY++;
		rotateZ++;
	}

	void Right()
	{
		rotateY--;
		rotateZ--;
	}

	void MorePower()
	{
		power++;
	}

	void LessPower()
	{
		power--;
	}

	void StartEngine(bool start)
	{
		startEngine = start;
	}

	void AbandoingWheels(bool abandoing)
	{
		abandonedWheels = abandoing;
	}

	GLfloat step = 0.0;
	GLfloat power = 0.0;
	GLfloat rotateX = 0.0;
	GLfloat rotateY = 0.0;
	GLfloat rotateZ = 0.0;
	GLfloat translateX = 0.0;
	GLfloat translateY = 0.0;
	GLfloat translateZ = 0.0;
	bool startEngine = false;
	bool abandonedWheels = false;


};
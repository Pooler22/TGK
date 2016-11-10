#pragma once
#include "Texturable.cpp"

class Sphere : public Texturable
{
public:
	explicit Sphere::Sphere(GLfloat x, GLfloat y, GLfloat z, GLfloat r, GLuint texture): Texturable(texture), x(x), y(y), z(z),r(r)
	{
		glEnable(GL_TEXTURE_2D);
		sphereObject = gluNewQuadric();
		gluQuadricDrawStyle(sphereObject, GLU_FILL);
		gluQuadricTexture(sphereObject, texture);
		gluQuadricNormals(sphereObject, GLU_SMOOTH);
	}

	void Sphere::Draw(GLfloat ruch) const
	{
		Texturable::Draw();

		glPushMatrix();
		
		glTranslatef(x, y + ruch, z);
		glRotatef(90, 1, 0, 0);
		gluSphere(sphereObject, r, 10, 10);

		glPopMatrix();
	}

	GLUquadric* sphereObject;
	GLfloat x; 
	GLfloat y;
	GLfloat z;
	GLfloat r;
};

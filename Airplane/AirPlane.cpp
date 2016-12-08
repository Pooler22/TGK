#include "AirPlane.h"
#include <gl/freeglut.h>


AirPlane::AirPlane(GLuint texture): Texturable(texture), model(0)
{
	modelAirplane.Load("airplane.ply");
	moveSpeed = moveSpeedStep;
	cam.updateVectors();
}

void AirPlane::increaseSpeed()
{
	moveSpeed += moveSpeedStep;
}

void AirPlane::decreaseSpeed()
{
	moveSpeed -= moveSpeedStep;
}

void AirPlane::updateCamera() const
{
	gluLookAt(cam.position.x,
	          cam.position.y,
	          cam.position.z,
	          cam.lookAt.x + cam.position.x,
	          cam.lookAt.y + cam.position.y,
	          cam.lookAt.z + cam.position.z,
	          cam.up.x,
	          cam.up.y,
	          cam.up.z);
}

void AirPlane::updateRoll(float deg)
{
	cam.roll(deg);
	cam.updateVectors();
}

void AirPlane::updatePitch(float deg)
{
	cam.pitch(deg);
	cam.updateVectors();
}

void AirPlane::moveForward(float sealevel)
{
	cam.position += cam.lookAt * moveSpeed;
}

void AirPlane::shootBullet()
{
	if (!bul.shooted)
	{
		bul = Bullet(cam.position);
		bul.setForward(cam.lookAt);
		bul.setShooted(true);
	}
}

void AirPlane::drawBullet()
{
	if (bul.shooted)
	{
		bul.moveForward();
		bul.drawBullet();
	}
}

void AirPlane::drawPlain()
{

	GLfloat tanamb[] = { 0.2,0.15,0.1,1.0 };
	GLfloat tandiff[] = { 0.4,0.3,0.2,1.0 };
	GLfloat tanspec[] = { 0.0,0.0,0.0,1.0 };

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, tanamb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, tandiff);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, tanspec);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 50.0);
	glTranslatef(0.17, -0.3, -.9);

	glPushMatrix();
	glScalef(0.0002, 0.0002, 0.0002);
	glRotatef(90, 1, 0, 0);
	glRotatef(-180, 0, 1, 0);
	modelAirplane.Draw();
	glPopMatrix();

//	glutSolidSphere(0.05f, 32, 16);
}

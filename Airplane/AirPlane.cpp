#include "AirPlane.h"
#include <gl/freeglut.h>


AirPlane::AirPlane(GLuint texture): Texturable(texture), model(0)
{
	moveSpeed = 0.005f;
	cam.updateVectors();
}

void AirPlane::increaseSpeed()
{
	moveSpeed += 0.001f;
}

void AirPlane::decreaseSpeed()
{
	moveSpeed -= 0.001f;
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

void AirPlane::drawPlain() const
{
	glTranslatef(cam.lookAt.x + cam.position.x,
	             cam.lookAt.y + cam.position.y,
	             cam.lookAt.z + cam.position.z);
	glutSolidSphere(0.05f, 32, 16);
}

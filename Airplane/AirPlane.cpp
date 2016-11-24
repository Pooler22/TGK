#include "AirPlane.h"
#include <gl/freeglut.h>


AirPlane::AirPlane()
{
	moveSpeed = 0.005f;
}

void AirPlane::updateCamera() const
{
	gluLookAt(cam.position.x,
	          cam.position.z,
	          cam.position.y,
	          cam.lookAt.x + cam.position.x,
	          cam.lookAt.z + cam.position.z,
	          cam.lookAt.y + cam.position.y,
	          cam.up.x,
	          cam.up.z,
	          cam.up.y);
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

void AirPlane::moveForward()
{
	cam.position = cam.position + cam.lookAt * moveSpeed;
}

void AirPlane::shootBullet()
{
	for (auto i = 0; i < MAX_BULLET; i++)
	{
		if (!bul[i].shooted)
		{
			bul[i] = Bullet(cam.position); // Set the initialize location of the bullet
			bul[i].setForward(cam.lookAt); // Set the foward vector of the bullet
			bul[i].setShooted(true); // Set a bool the bullet shooted or not.
		}
	}
}

void AirPlane::drawBullet()
{
	for (auto i = 0; i < MAX_BULLET; i++)
	{
		if (bul[i].shooted)
		{
			bul[i].moveForward();
			bul[i].drawBullet();
		}
	}
}

void AirPlane::drawPlain()
{
	/*glTranslatef(cam.position.x+ cam.lookAt.x, cam.position.y + cam.lookAt.x, cam.position.y + cam.lookAt.z);
	glutSolidSphere(0.05f, 32, 16);*/
}

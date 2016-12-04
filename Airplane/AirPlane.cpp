#include "AirPlane.h"
#include <gl/freeglut.h>


AirPlane::AirPlane()
{
	moveSpeed = 0.005f;
	flaing = true;
}

void AirPlane::increaseSpeed()
{
	moveSpeed += 0.001;
}

void AirPlane::decreaseSpeed()
{
	moveSpeed -= 0.001;
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
	if(abs(sealevel - cam.position.z) > 0.01)
	{
		cam.position.z -= 0.001;
	}
}

void AirPlane::shootBullet()
{
	for (auto i = 0; i < MAX_BULLET; i++)
	{
		if (!bul[i].shooted)
		{
			bul[i] = Bullet(cam.position);
			bul[i].setForward(cam.lookAt);
			bul[i].setShooted(true);
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

void AirPlane::drawPlain() const
{
	glTranslatef(cam.lookAt.x + cam.position.x,
	             cam.lookAt.y + cam.position.y,
	             cam.lookAt.z + cam.position.z);
	glutSolidSphere(0.05f, 32, 16);
}

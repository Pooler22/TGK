#include "Bullet.h"
#include <gl/freeglut.h>

Bullet::Bullet(): shooted(false)
{
	cood = Vector3(0, 0, 0);
	forward = Vector3(1, 0, 0);
	moveSpeed = 0.1f;
	counter = 0;
}

Bullet::Bullet(Vector3 vec): shooted(false)
{
	cood = vec;
	forward = Vector3(1, 0, 0);
	moveSpeed = 0.1f;
	counter = 0;
}

void Bullet::setForward(Vector3 vec)
{
	forward = vec;
}

void Bullet::moveForward()
{
	cood = cood + forward * moveSpeed;
}

void Bullet::drawBullet()
{
	if (counter < 50)
	{
		glTranslatef(cood.x, cood.z, cood.y);
		glutSolidSphere(0.05f, 32, 16);
		counter++;
	}
	else
	{
		shooted = !shooted;
	}
}

void Bullet::setShooted(bool b)
{
	shooted = b;
}

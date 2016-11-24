#include "Bullet.h"
#include <gl/freeglut.h>

Bullet::Bullet(): shooted(false)
{
	cood = glm::vec3(0, 0, 0);
	forward = glm::vec3(1, 0, 0);
	moveSpeed = 0.1f;
	counter = 0;
}

Bullet::Bullet(glm::vec3 vec): shooted(false)
{
	cood = vec;
	forward = glm::vec3(1, 0, 0);
	moveSpeed = 0.1f;
	counter = 0;
}

void Bullet::setForward(glm::vec3 vec)
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

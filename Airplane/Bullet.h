#ifndef Bullet_h
#define Bullet_h

#include "Vector3.h"

class Bullet
{
public:
	int counter;
	bool shooted;
	Vector3 cood;
	Vector3 forward;
	float moveSpeed;
	Bullet();
	explicit Bullet(Vector3 vec);
	void moveForward();
	void setForward(Vector3 vec);
	void drawBullet();
	void setShooted(bool b);
};

#endif

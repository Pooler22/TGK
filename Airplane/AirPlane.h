#ifndef AirPlane_h
#define AirPlane_h

#define MAX_BULLET 1

#include "Camera.h"
#include "Bullet.h"

class AirPlane
{
public:
	bool flaing;
	float moveSpeed;
	Camera cam;
	Bullet bul[MAX_BULLET];

	AirPlane();
	void updateCamera() const;
	void updateRoll(float deg);
	void updatePitch(float deg);
	void moveForward(float sealevel);
	void increaseSpeed();
	void decreaseSpeed();
	void shootBullet();
	void drawBullet();
	void drawPlain() const;
};

#endif

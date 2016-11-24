#ifndef AirPlane_h
#define AirPlane_h

#define MAX_BULLET 1

#include "Camera.h"
#include "Bullet.h"

class AirPlane
{
public:
	float moveSpeed;
	Camera cam;
	Bullet bul[MAX_BULLET];
	AirPlane();
	void updateCamera() const;
	void updateRoll(float deg);
	void updatePitch(float deg);
	void moveForward();
	void shootBullet();
	void drawBullet();
	void drawPlain();
};

#endif

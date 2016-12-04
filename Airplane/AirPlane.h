#ifndef AirPlane_h
#define AirPlane_h

#include "Camera.h"
#include "Bullet.h"

class AirPlane
{
public:
	float moveSpeed;
	Camera cam;
	Bullet bul;

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

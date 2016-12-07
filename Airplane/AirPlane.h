#ifndef AirPlane_h
#define AirPlane_h

#include "Texturable.h"
#include "Camera.h"
#include "Bullet.h"

class AirPlane : public Texturable
{
public:
	float moveSpeed;
	Camera cam;
	Bullet bul;
	GLuint model;

	explicit AirPlane(GLuint texture);
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

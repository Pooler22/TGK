#ifndef AirPlane_h
#define AirPlane_h

#include "Texturable.h"
#include "Camera.h"
#include "Bullet.h"
#include "Model.h"

class AirPlane : public Texturable
{
public:
	const float moveSpeedStep = 0.001f;
	float moveSpeed;
	Camera cam;
	Bullet bul;
	GLuint model;
	Model modelAirplane;

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

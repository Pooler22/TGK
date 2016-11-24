#ifndef Camera_h
#define Camera_h

#include "Vector3.h"
#include "Quaternion.h"

class Camera
{
public:
	Quaternion rotation;
	Vector3 position;
	Vector3 lookAt;
	Vector3 up;
	Camera();
	void roll(float r);
	void pitch(float r);
	void updateVectors();
};

#endif

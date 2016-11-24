#ifndef Camera_h
#define Camera_h

#include "glm/glm.hpp"
#include "Quaternion.h"

class Camera
{
public:
	Quaternion rotation;
	glm::vec3 position;
	glm::vec3 lookAt;
	glm::vec3 up;
	Camera();
	void roll(float r);
	void pitch(float r);
	void updateVectors();
};

#endif

#include "Camera.h"
#include <glm/glm.hpp>

Camera::Camera() {
	position = Vector3(0, 0.05, 0);
	rotation = Quaternion(1.0, 0.0, 0.0, 0.0);
	lookAt = Vector3(1, 0, 0);
	up = Vector3(0, 1, 0);
	rotation.normalise();
}

void Camera::roll(float r) {
	auto v = rotation * Vector3(1.0, 0.0, 0.0);
	Quaternion nrot(r, v.x, v.y, v.z);
	nrot.normalise();
	rotation = nrot * rotation;
	rotation.normalise();
}

void Camera::pitch(float r) {
	auto v = rotation * Vector3(0.0, 0.0, 1.0);
	Quaternion nrot(r, v.x, v.y, v.z);
	nrot.normalise();
	rotation = nrot * rotation;
	rotation.normalise();
}

void Camera::updateVectors() {
	auto v = rotation * Vector3(1.0, 0.0, 0.0);
	lookAt.x = v.x;
	lookAt.y = v.y;
	lookAt.z = v.z;

	v = rotation * Vector3(0.0, 1.0, 0.0);
	up.x = v.x;
	up.y = v.y;
	up.z = v.z;
}

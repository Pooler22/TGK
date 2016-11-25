#include "Camera.h"
#include <glm/glm.hpp>

Camera::Camera()
{
	position = glm::vec3(0, 0.05, 0);
	rotation = normalize(glm::vec4(0.0, 0.0, 0.0, 1.0));
	lookAt = glm::vec3(1, 0, 0);
	up = glm::vec3(0, 1, 0);
}

glm::vec4 op1(glm::vec4& rq1, glm::vec4& rq)
{
	return glm::vec4(
		rq1.w * rq.x + rq1.x * rq.w + rq1.y * rq.z - rq1.z * rq.y,
		rq1.w * rq.y + rq1.y * rq.w + rq1.z * rq.x - rq1.x * rq.z,
		rq1.w * rq.z + rq1.z * rq.w + rq1.x * rq.y - rq1.y * rq.x,
		rq1.w * rq.w - rq1.x * rq.x - rq1.y * rq.y - rq1.z * rq.z
	);
}

glm::vec3 op2(glm::vec4 a, glm::vec3& vec)
{
	return glm::vec3(op1(op1(a, glm::vec4(normalize(vec), 0.0)), *new glm::vec4(glm::vec3(-a), a.w)));
}

void Camera::roll(float r)
{
	rotation = normalize(op1(normalize(glm::vec4(op2(rotation, *new glm::vec3(1.0, 0.0, 0.0)), r)), rotation));
}

void Camera::pitch(float r)
{
	rotation = normalize(op1(normalize(glm::vec4(op2(rotation, glm::vec3(0.0, 0.0, 1.0)), r)), rotation));
}

void Camera::updateVectors()
{
	lookAt = op2(rotation, *new glm::vec3(1.0, 0.0, 0.0));
	up = op2(rotation, *new glm::vec3(0.0, 1.0, 0.0));
}

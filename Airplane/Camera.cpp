#include "Camera.h"
#include <glm/gtx/vector_angle.hpp>
#include <iostream>

Camera::Camera()
{
	rotation = glm::vec4(1.f, 0.f, 0.f, 1.f);
	position = glm::vec3(0.f, 0.f, 0.f);
	lookAt = glm::vec3(0.f, 1.f, 0.f);
	up = glm::vec3(1.f, 0.f, 0.f);
}

glm::vec4 op1(glm::vec4& rq1, glm::vec4& rq2)
{
	return glm::vec4(
		rq1.w * rq2.x + rq1.x * rq2.w + rq1.y * rq2.z - rq1.z * rq2.y,
		rq1.w * rq2.y + rq1.y * rq2.w + rq1.z * rq2.x - rq1.x * rq2.z,
		rq1.w * rq2.z + rq1.z * rq2.w + rq1.x * rq2.y - rq1.y * rq2.x,
		rq1.w * rq2.w - rq1.x * rq2.x - rq1.y * rq2.y - rq1.z * rq2.z
	);
}

glm::vec3 op2(glm::vec4 a, glm::vec3& vec)
{
	return glm::vec3(op1(op1(a, glm::vec4((vec), 0.0)), *new glm::vec4(glm::vec3(-a), a.w)));
}

void Camera::roll(float r)
{
	rotation = normalize(op1((glm::vec4(op2(rotation, glm::vec3(1.0, 0.0, 0.0)), r)), rotation));
}

void Camera::pitch(float r)
{
	rotation = normalize(op1((glm::vec4(op2(rotation, glm::vec3(0.0, 0.0, 1.0)), r)), rotation));
}

void Camera::yaw(float r)
{
	rotation = normalize(op1((glm::vec4(op2(rotation, glm::vec3(0.0, 1.0, 0.0)), r)), rotation));
}

void Camera::updateVectors()
{
	lookAt = op2(rotation, *new glm::vec3(1.0, 0.0, 0.0));
	up = op2(rotation, *new glm::vec3(0.0, 1.0, 0.0));
}

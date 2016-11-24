#include "Vector3.h"
#include <math.h>

Vector3::Vector3(): x(0), y(0), z(0)
{
}

Vector3::Vector3(float a, float b, float c)
{
	x = a;
	y = b;
	z = c;
}

void Vector3::normalize()
{
	auto m = x * x + y * y + z * z;
	if (fabsf(m) > TOLERANCE && fabsf(m - 1.0f) > TOLERANCE)
	{
		auto mag = sqrtf(m);
		x /= mag;
		y /= mag;
		z /= mag;
	}
}

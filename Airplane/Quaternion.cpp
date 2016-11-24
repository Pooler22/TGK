#include "Quaternion.h"
#include <math.h>

#define DEGREE 60
#define TOLERANCE  0.00001f
#define PI 3.14159
#define PIOVER180 PI/180

Quaternion::Quaternion(float a, float b, float c, float d){
	w = a;
	x = b;
	y = c;
	z = d;
}

Quaternion::Quaternion()
{
}

void Quaternion::normalise()
{
	auto m = x * x + y * y + z * z + w * w;
	if (fabsf(m) > TOLERANCE && fabsf(m - 1.0f) > TOLERANCE)
	{
		auto mag = sqrtf(m);
		w /= mag;
		x /= mag;
		y /= mag;
		z /= mag;
	}
}

Quaternion Quaternion::getConjugate() const
{
	return Quaternion(w, -x, -y, -z);
}

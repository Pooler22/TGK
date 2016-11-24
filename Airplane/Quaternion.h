#ifndef Quaternion_h
#define Quaternion_h

#include "Vector3.h"

class Quaternion
{
public:
	float w, x, y, z;
	Quaternion(float a, float b, float c, float d);
	Quaternion();
	void normalise();
	Quaternion getConjugate() const;
	void FromEuler(float pitch, float yaw, float roll);

	// Multiplying q1 with q2 applies the rotation q2 to q1
	Quaternion operator*(const Quaternion& rq) const
	{
		return Quaternion(
			w * rq.w - x * rq.x - y * rq.y - z * rq.z,
			w * rq.x + x * rq.w + y * rq.z - z * rq.y,
			w * rq.y + y * rq.w + z * rq.x - x * rq.z,
			w * rq.z + z * rq.w + x * rq.y - y * rq.x
		);
	}

	// Multiplying a quaternion q with a vector vec applies the q-rotation to vec
	// This method is used by Camera::updateVectors().
	Vector3 operator*(const Vector3& vec) const
	{
		Vector3 vn(vec.x, vec.y, vec.z);
		vn.normalize();
		Quaternion vecQuat, resQuat;
		vecQuat.x = vn.x;
		vecQuat.y = vn.y;
		vecQuat.z = vn.z;
		vecQuat.w = 0.0;
		resQuat = vecQuat * getConjugate();
		resQuat = *this * resQuat;
		return Vector3(resQuat.x, resQuat.y, resQuat.z);
	}
};

#endif

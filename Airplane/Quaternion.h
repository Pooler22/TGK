#ifndef Quaternion_h
#define Quaternion_h

#include <glm/glm.hpp>

class Quaternion: glm::vec4
{
public:
	Quaternion(float a, float b, float c, float d);
	Quaternion();
	void normalise();
	Quaternion getConjugate() const;

	Quaternion operator*(const Quaternion& rq) const
	{
		return Quaternion(
			w * rq.w - x * rq.x - y * rq.y - z * rq.z,
			w * rq.x + x * rq.w + y * rq.z - z * rq.y,
			w * rq.y + y * rq.w + z * rq.x - x * rq.z,
			w * rq.z + z * rq.w + x * rq.y - y * rq.x
		);
	}

	glm::vec3 operator*(const glm::vec3& vec) const
	{
		glm::vec3 vn(vec.x, vec.y, vec.z);
		vn = normalize(vn);
		Quaternion vecQuat, resQuat;
		vecQuat.x = vn.x;
		vecQuat.y = vn.y;
		vecQuat.z = vn.z;
		vecQuat.w = 0.0;
		resQuat = vecQuat * getConjugate();
		resQuat = *this * resQuat;
		return glm::vec3(resQuat.x, resQuat.y, resQuat.z);
	}
};

#endif

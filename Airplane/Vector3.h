#ifndef Vector3_h
#define Vector3_h

#define DEGREE 60
#define TOLERANCE  0.00001f
#define PI 3.14159
#define PIOVER180 PI/180

class Vector3
{
public:
	float x, y, z;

	Vector3();
	Vector3(float a, float b, float c);

	Vector3 operator+(const Vector3 v) const
	{
		return Vector3(x + v.x, y + v.y, z + v.z);
	};

	Vector3 operator-(const Vector3 v) const
	{
		return Vector3(x - v.x, y - v.y, z - v.z);
	};

	Vector3 operator*(const float f) const
	{
		return Vector3(x * f, y * f, z * f);
	};

	Vector3 operator/(const float f) const
	{
		return Vector3(x / f, y / f, z / f);
	};

	void normalize();
};


#endif

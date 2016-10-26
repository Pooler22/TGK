#pragma once
#include <vector>

class Triangle
{
public:
	Triangle(std::vector<float>, float*);
	void Draw() const;
	float* a;
	float* b;
	float* c;
	float* color;
};

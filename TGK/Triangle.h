#pragma once
#include <vector>

class Triangle
{
public:
	Triangle(std::vector<GLfloat>, GLfloat*);
	void Draw() const;
	GLfloat* a;
	GLfloat* b;
	GLfloat* c;
	GLfloat* color;
};

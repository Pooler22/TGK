#ifndef Mountain_h
#define Mountain_h

#include <gl/freeglut.h>

#define ADDR(i,j,k) (3*((j)*res + (i)) + (k))

class Mountain
{
public:

	GLfloat* verts = nullptr;
	GLfloat* norms = nullptr;
	GLuint* faces = nullptr;

	int res = 513;
	static float randomize(float x, float y);
	void mountain(int i, int j, int s) const;
	void makemountain();
};

#endif

#ifndef ParticleSystem_h
#define ParticleSystem_h

#include <gl/freeglut.h>
#include "System.h"

class ParticleSystem
{
public:
	GLfloat texture_t[10];
	System particleSystem;

	void drawParticles(void);
	void init();
	void draw();
};

#endif

#include "ParticleSystem.h"
#include <gl/freeglut.h>

void ParticleSystem::init()
{
	//texture_t[0] = Texturable::LoadTextureRAW("particle_mask.raw", 256, 256); //load alpha for texture_t
	//texture_t[1] = Texturable::LoadTextureRAW("particle.raw", 256, 256); //load texture_t
	particleSystem.setSystemType(4);
	particleSystem.createParticles();
}

void ParticleSystem::draw()
{
	glPushMatrix();
	particleSystem.updateParticles();
	drawParticles();
	glPopMatrix();
}

void ParticleSystem::drawParticles(void)
{
	glScalef(0.1, 0.1, 0.1);
	glRotatef(90, 1, 0, 0);
	glTranslatef(0, 5, 4);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(0.4, 0.0, 0.0);
	for (auto i = 1; i < particleSystem.getNumOfParticles(); i++)
	{
		glPushMatrix();
		// set color and fade value (alpha) of current particle
		glColor4f(particleSystem.getR(i), particleSystem.getG(i), particleSystem.getB(i), particleSystem.getAlpha(i));
		// move the current particle to its new position
		glTranslatef(particleSystem.getXPos(i), particleSystem.getYPos(i), particleSystem.getZPos(i)); //+ zoom
		// rotate the particle (this is proof of concept for when proper smoke texture_t is added)
		glRotatef(particleSystem.getDirection(i) - 0, 0, 0, 1);
		// scale the wurrent particle (only used for smoke)
		glScalef(particleSystem.getScale(i), particleSystem.getScale(i), particleSystem.getScale(i));

		//glDisable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);

		glBlendFunc(GL_DST_COLOR, GL_ZERO);
		glBindTexture(GL_TEXTURE_2D, texture_t[0]);

		glBegin(GL_QUADS);
		glTexCoord2d(0, 0);
		glVertex3f(-0.1, -0.1, 0);
		glTexCoord2d(0.1, 0);
		glVertex3f(0.1, -0.1, 0);
		glTexCoord2d(0.1, 0.1);
		glVertex3f(0.1, 0.1, 0);
		glTexCoord2d(0, 0.1);
		glVertex3f(-0.1, 0.1, 0);
		glEnd();

		glBlendFunc(GL_ONE, GL_ONE);
		glBindTexture(GL_TEXTURE_2D, texture_t[1]);

		glBegin(GL_QUADS);
		glTexCoord2d(0, 0);
		glVertex3f(-0.1, -0.1, 0);
		glTexCoord2d(0.1, 0);
		glVertex3f(0.1, -0.1, 0);
		glTexCoord2d(0.1, 0.1);
		glVertex3f(0.1, 0.1, 0);
		glTexCoord2d(0, 0.1);
		glVertex3f(-0.1, 0.1, 0);
		glEnd();

		glEnable(GL_DEPTH_TEST);

		glPopMatrix();
	}
}

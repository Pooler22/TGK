#pragma once
#include <GL/freeglut.h>

class Texturable
{
public:
	explicit Texturable::Texturable(GLuint textureInit)
	{
		texture = textureInit;
	}

	void Texturable::Draw() const
	{
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}

	GLuint texture;
};

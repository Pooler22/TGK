#ifndef Texturable_h
#define Texturable_h

#include <gl/freeglut.h>

class Texturable
{
public:
	GLuint texture;
	explicit Texturable::Texturable(GLuint textureInit);
	void Texturable::Draw() const;
	static GLuint Texturable::LoadTexture(const char* filename);
	GLuint LoadTextureRAW(const char* filename, int width, int height);
	void FreeTexture(GLuint texture_t);
};

#endif

#pragma once
#include <GL/freeglut.h>
#include <iostream>

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

	static GLuint Texturable::LoadTexture(const char* filename)
	{
		GLuint texture;
		int width, height, size;
		unsigned char* data;
		FILE* file;

		width = 256;
		height = 256;
		size = width * height * 3;

		fopen_s(&file, filename, "rb");
		if (file == nullptr) return 0;
		data = static_cast<unsigned char *>(malloc(size));
		fread(data, size, 1, file);
		fclose(file);

		for (auto i = 0; i < size; i += 3)
		{
			std::swap(data[i], data[i + 2]);
		}

		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
		free(data);

		return texture;
	}
};

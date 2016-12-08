#include "ObjLoader.h"
#include <cstdio>
#include <GL/gl.h>
#include <vector>

GLuint ObjLoader::loadObj(char* fname)
{
	auto mdoel = std::vector<float[3]>();;
	GLuint loaded_objcet;
	FILE* fp;
	int read;
	GLfloat x, y, z;
	auto ch = '1';
	loaded_objcet = glGenLists(1);
	fopen_s(&fp, fname, "r");
	if (!fp)
	{
		printf("can't open file %s\n", fname);
		exit(1);
	}
	glPointSize(2.0);
	glNewList(loaded_objcet, GL_COMPILE);
	{
		glPushMatrix();
		glBegin(GL_POINTS);
		while (!feof(fp))
		{
			read = fscanf_s(fp, "%c %f %f %f", &ch, &x, &y, &z);
			if (read == 4 && ch == 'v')
			{
				glVertex3f(x, y, z);
			}
		}
		glEnd();
	}
	glPopMatrix();
	glEndList();
	fclose(fp);

	return loaded_objcet;
}

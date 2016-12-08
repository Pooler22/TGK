#include "Mountain.h"
#include <glm/detail/type_vec3.hpp>
#include <cmath>

#define ADDR(i,j,k) (3*((j)*res + (i)) + (k))

float Mountain::randomize(float x, float y)
{
	static auto a = 1688135690, b = 11176900;
	srand(int(x) * a % b - int(y) * b % a);
	return 2.0f * (float(rand()) / float(RAND_MAX)) - 1.0f;
}

void Mountain::mountain(int i, int j, int s) const
{
	if (s > 1)
	{
		auto x0 = glm::vec3(verts[ADDR(i, j, 0)], verts[ADDR(i, j, 1)], verts[ADDR(i, j, 2)]);
		auto x1 = glm::vec3(verts[ADDR(i + s, j, 0)], verts[ADDR(i + s, j, 1)], verts[ADDR(i + s, j, 2)]);
		auto x2 = glm::vec3(verts[ADDR(i, j + s, 0)], verts[ADDR(i, j + s, 1)], verts[ADDR(i, j + s, 2)]);
		auto x3 = glm::vec3(verts[ADDR(i + s, j + s, 0)], verts[ADDR(i + s, j + s, 1)], verts[ADDR(i + s, j + s, 2)]);

		auto x01 = 0.5f * (x0 + x1);
		auto x02 = 0.5f * (x0 + x2);
		auto x13 = 0.5f * (x1 + x3);
		auto x23 = 0.5f * (x2 + x3);
		auto x0123 = 0.25f * (x0 + x1 + x2 + x3);

		x01.z += 0.5f * (float(s) / res) * randomize(x01.x, x01.y);
		x02.z += 0.5f * (float(s) / res) * randomize(x02.x, x02.y);
		x13.z += 0.5f * (float(s) / res) * randomize(x13.x, x13.y);
		x23.z += 0.5f * (float(s) / res) * randomize(x23.x, x23.y);
		x0123.z += 0.5f * (float(s) / res) * randomize(x0123.x, x0123.y);

		verts[ADDR(i + s / 2, j, 0)] = x01.x;
		verts[ADDR(i + s / 2, j, 1)] = x01.y;
		verts[ADDR(i + s / 2, j, 2)] = x01.z;

		verts[ADDR(i, j + s / 2, 0)] = x02.x;
		verts[ADDR(i, j + s / 2, 1)] = x02.y;
		verts[ADDR(i, j + s / 2, 2)] = x02.z;

		verts[ADDR(i + s, j + s / 2, 0)] = x13.x;
		verts[ADDR(i + s, j + s / 2, 1)] = x13.y;
		verts[ADDR(i + s, j + s / 2, 2)] = x13.z;

		verts[ADDR(i + s / 2, j + s, 0)] = x23.x;
		verts[ADDR(i + s / 2, j + s, 1)] = x23.y;
		verts[ADDR(i + s / 2, j + s, 2)] = x23.z;

		verts[ADDR(i + s / 2, j + s / 2, 0)] = x0123.x;
		verts[ADDR(i + s / 2, j + s / 2, 1)] = x0123.y;
		verts[ADDR(i + s / 2, j + s / 2, 2)] = x0123.z;

		mountain(i, j, s / 2);
		mountain(i + s / 2, j, s / 2);
		mountain(i, j + s / 2, s / 2);
		mountain(i + s / 2, j + s / 2, s / 2);
	}
	else
	{
		float dx, dy, dz;

		if (i == 0)
		{
			dx = verts[ADDR(i + 1, j, 2)] - verts[ADDR(i, j, 2)];
		}
		else if (i == res - 1)
		{
			dx = verts[ADDR(i, j, 2)] - verts[ADDR(i - 1, j, 2)];
		}
		else
		{
			dx = (verts[ADDR(i + 1, j, 2)] - verts[ADDR(i - 1, j, 2)]) / 2.0f;
		}

		if (j == 0)
		{
			dy = verts[ADDR(i, j + 1, 2)] - verts[ADDR(i, j, 2)];
		}
		else if (j == res - 1)
		{
			dy = verts[ADDR(i, j, 2)] - verts[ADDR(i, j - 1, 2)];
		}
		else
		{
			dy = (verts[ADDR(i, j + 1, 2)] - verts[ADDR(i, j - 1, 2)]) / 2.0f;
		}

		dx *= res;
		dy *= res;
		dz = 1.0f / sqrt(dx * dx + dy * dy + 1.0f);
		dx *= dz;
		dy *= dz;

		norms[ADDR(i, j, 0)] = dx;
		norms[ADDR(i, j, 1)] = dy;
		norms[ADDR(i, j, 2)] = dz;
	}
}

void Mountain::makemountain()
{
	int i, j;

	if (verts) free(verts);
	if (norms) free(norms);
	if (faces) free(faces);

	verts = static_cast<GLfloat *>(malloc(res * res * 3 * sizeof(GLfloat)));
	norms = static_cast<GLfloat *>(malloc(res * res * 3 * sizeof(GLfloat)));
	faces = static_cast<GLuint *>(malloc((res - 1) * (res - 1) * 6 * sizeof(GLuint)));

	verts[ADDR(0, 0, 0)] = -5.0;
	verts[ADDR(0, 0, 1)] = -5.0;
	verts[ADDR(0, 0, 2)] = 0.0;

	verts[ADDR(res - 1, 0, 0)] = 5.0;
	verts[ADDR(res - 1, 0, 1)] = -5.0;
	verts[ADDR(res - 1, 0, 2)] = 0.0;

	verts[ADDR(0, res - 1, 0)] = -5.0;
	verts[ADDR(0, res - 1, 1)] = 5.0;
	verts[ADDR(0, res - 1, 2)] = 0.0;

	verts[ADDR(res - 1, res - 1, 0)] = 5.0;
	verts[ADDR(res - 1, res - 1, 1)] = 5.0;
	verts[ADDR(res - 1, res - 1, 2)] = 0.0;

	mountain(0, 0, res - 1);

	auto f = faces;
	for (j = 0; j < res - 1; j++)
	{
		for (i = 0; i < res - 1; i++)
		{
			*f++ = j * res + i;
			*f++ = j * res + i + 1;
			*f++ = (j + 1) * res + i + 1;
			*f++ = j * res + i;
			*f++ = (j + 1) * res + i + 1;
			*f++ = (j + 1) * res + i;
		}
	}
}

#pragma once
#include <GL/freeglut.h>
#include <vector>
#include "Point.cpp"

class Square
{
public:
	explicit Square::Square(GLfloat n[4][3])
	{
		points = std::vector<Point>();
		for (auto i = 0; i < 4; i++)
		{
			points.push_back(Point(n[i][0], n[i][1], n[i][2]));
		}
	}

	void Square::Draw() const
	{
		glBegin(GL_QUADS);

		glTexCoord2f(0.0, 0.0);
		points.at(0).Draw();
		glTexCoord2f(0.0, 1.0);
		points.at(1).Draw();
		glTexCoord2f(1.0, 1.0);
		points.at(2).Draw();
		glTexCoord2f(1.0, 0.0);
		points.at(3).Draw();

		glEnd();
	}

	std::vector<Point> points;
};

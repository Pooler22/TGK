#pragma once
#include <GL/freeglut.h>
#include <vector>
#include <memory>
#include "Texturable.cpp"
#include "Square.cpp"

class Cube: public Texturable
{
public:
	Cube::Cube(GLfloat x, GLfloat y, GLfloat z, GLfloat n, GLuint texure) : Texturable(texure)
	{
		squares = std::make_unique<std::vector<Square>>();

		squares->push_back(Square(new GLfloat[4][3]{
			{x - n,y - n,z - n},
			{x + n,y - n,z - n},
			{x + n,y + n,z - n},
			{x - n,y + n,z - n}
		}));
		squares->push_back(Square(new GLfloat[4][3]{
			{x - n,y - n,z + n},
			{x + n,y - n,z + n},
			{x + n,y + n,z + n},
			{x - n,y + n,z + n}
		}));
		squares->push_back(Square(new GLfloat[4][3]{
			{x - n,y - n,z - n},
			{x - n,y + n,z - n},
			{x - n,y + n,z + n},
			{x - n,y - n,z + n}
		}));
		squares->push_back(Square(new GLfloat[4][3]{
			{x + n,y - n,z - n},
			{x + n,y + n,z - n},
			{x + n,y + n,z + n},
			{x + n,y - n,z + n}
		}));
		squares->push_back(Square(new GLfloat[4][3]{
			{x - n,y - n,z - n},
			{x + n,y - n,z - n},
			{x + n,y - n,z + n},
			{x - n,y - n,z + n}
		}));
		squares->push_back(Square(new GLfloat[4][3]{
			{x - n,y + n,z - n},
			{x + n,y + n,z + n},
			{x + n,y + n,z + n},
			{x - n,y + n,z - n}
		}));
	}

	void Cube::Draw() const
	{
		glPushMatrix();
		Texturable::Draw();
		for (auto square : *squares)
		{
			square.Draw();
		}
		glPopMatrix();
	}

	std::unique_ptr<std::vector<Square>> squares;
};

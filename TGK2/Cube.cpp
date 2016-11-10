#include <GL/freeglut.h>
#include <vector>
#include <memory>
#include "Square.cpp"

class Cube
{
public:
	Cube::Cube(GLfloat x, GLfloat y, GLfloat z, GLfloat n)
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
		for (auto square : *squares)
		{
			square.Draw();
		}
	}

	std::unique_ptr<std::vector<Square>> squares;
};

#ifndef Bullet_h
#define Bullet_h

#include "glm/glm.hpp"

class Bullet
{
public:
	int counter;
	bool shooted;
	float moveSpeed;
	glm::vec3 cood;
	glm::vec3 forward;

	Bullet();
	explicit Bullet(glm::vec3);
	void moveForward();
	void setForward(glm::vec3 vec);
	void drawBullet();
	void setShooted(bool b);
};

#endif

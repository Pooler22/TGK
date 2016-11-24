#ifndef Bullet_h
#define Bullet_h

#include "glm/glm.hpp"

class Bullet
{
public:
	int counter;
	bool shooted;
	glm::vec3 cood;
	glm::vec3 forward;
	float moveSpeed;
	Bullet();
	explicit Bullet(glm::vec3 vec);
	void moveForward();
	void setForward(glm::vec3 vec);
	void drawBullet();
	void setShooted(bool b);
};

#endif

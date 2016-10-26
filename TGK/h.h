/**
*  BadproG.com
*  h.h
*/

#ifndef H_H_
#define H_H_

/**
* Define
*/
#define SCREEN_TITLE         "Hello World! :D"
#define SCREEN_WIDTH         600
#define SCREEN_HEIGHT         600
#define SCREEN_POSITION_X     100
#define SCREEN_POSITION_Y     100
#include <GL/gl.h>

/**
* Structure
*/
typedef struct s_badprog
{
	int screenPositionX;
	int screenPositionY;

	double side;
	double hyp;
	double sideHalf;
	double sideToFind;
	double ratio;

	GLclampf bgRed;
	GLclampf bgGreen;
	GLclampf bgBlue;
	GLclampf bgAlpha;

	GLfloat drawRed;
	GLfloat drawGreen;
	GLfloat drawBlue;

	GLfloat z;
	GLfloat x1;
	GLfloat x2;
	GLfloat x3;
	GLfloat y1;
	GLfloat y2;
	GLfloat y3;
} t_badprog;

#endif /* H_H_ */

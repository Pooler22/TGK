#include "Menu.h"
#include <GL/freeglut.h>

void Menu::drawStrings() const
{
	glColor3d(0.0f, 0.0f, 0.0f);
	ds.draw("    h - show/hide help", GLUT_WINDOW_WIDTH, GLUT_WINDOW_HEIGHT, 1, 5);
	if (showHelp)
	{
		ds.draw("   UP - pitch down", GLUT_WINDOW_WIDTH, GLUT_WINDOW_HEIGHT, 1, 10);
		ds.draw(" Down - pitch up", GLUT_WINDOW_WIDTH, GLUT_WINDOW_HEIGHT, 1, 14);
		ds.draw(" Left - roll left", GLUT_WINDOW_WIDTH, GLUT_WINDOW_HEIGHT, 1, 18);
		ds.draw("Right - roll right", GLUT_WINDOW_WIDTH, GLUT_WINDOW_HEIGHT, 1, 22);
		ds.draw("  +   - sea level up", GLUT_WINDOW_WIDTH, GLUT_WINDOW_HEIGHT, 1, 26);
		ds.draw("  -   - sea level down", GLUT_WINDOW_WIDTH, GLUT_WINDOW_HEIGHT, 1, 30);
		ds.draw("Space - shoot", GLUT_WINDOW_WIDTH, GLUT_WINDOW_HEIGHT, 1, 34);
	}
}

void Menu::changeVisibilityMenu()
{
	showHelp = !showHelp;
}

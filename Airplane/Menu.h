#ifndef Menu_h
#define Menu_h

#include "DrawString.h"

class Menu
{
public:
	DrawString ds;
	bool showHelp = true;

	void drawStrings() const;
	void changeVisibilityMenu();
};
#endif

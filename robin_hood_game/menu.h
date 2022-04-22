#pragma once

#include "display.h"
#include <Windows.h>


/*
	Menu object is created when game is paused
	Does not relate to any other class 
	Simply used to get user input
*/

class Menu {
public:
	Menu();	
	int listenInput();
	void drawMenu();
private:
	int width, height, x, y, state;
};


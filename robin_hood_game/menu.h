#pragma once

#include "display.h"
#include <Windows.h>

class Menu {
public:
	Menu();	
	int listenInput();
	void drawMenu();
private:
	int width, height, x, y, state;
};


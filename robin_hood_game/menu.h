#pragma once

#include "display.h"
#include <Windows.h>

class Menu {
public:
	Menu();
	int width, height, x, y, state;
	int listenInput();
	void drawMenu();
};


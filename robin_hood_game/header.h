#pragma once

#include "config.h"
#include "display.h"
#include "widget.h"



class Header {
public:
	Header(int level, int* lives);
	int numbers[10][10][8];
	void update();
private:
	int level, livesPrev;
	int* lives;
	void setBackground();
	Level levelWidget;
	Lives livesWidget;
};


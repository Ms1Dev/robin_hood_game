#pragma once

#include "config.h"
#include "display.h"
#include <string>


class Widget {
protected:
	struct Image {
		int height, width, x, y;
		int *imgData[];
	};
public:
	Widget();
	static void addToDisplay(Image *image);
	void update();
	static void setNumbers();
protected:
	static int numbers[10][10][8];
	int height, width, x, y;
	string imageFile;
};


class Level : Widget {
public:
	Level(int* value);
	void update();
private:
	int* value;
	int numPosx, numPosy;
};


class Header {
public:
	Header();
	int numbers[10][10][8];
	void update();
private:
	int level;
	void setBackground();
	Level levelWidget;
};


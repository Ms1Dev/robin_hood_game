#pragma once

#include <string>

/* 
	base class for widgets in the header showing current leveland lives
*/

class Widget {
protected:
	struct Image {
		int height, width, x, y;
		int* imgData[];
	};
public:
	Widget();
	static void addToDisplay(Image* image);
	void update();
	static void setNumbers();
protected:
	static int numbers[10][10][8];
	int height, width, x, y;
	std::string imageFile;
	int itemPosx, itemPosy;
};


/*
	Level widget displays the current level and shown in the header
*/

class Level : public Widget {
public:
	Level();
	void update(int value);
};

/*
	Lives widget shows the remaining lives of the player in the header
*/

class Lives : public Widget {
public:
	Lives();
	void update(int value);
};


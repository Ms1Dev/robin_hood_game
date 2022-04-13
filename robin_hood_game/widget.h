#pragma once

#include <string>

// base class for widgets in the header showing current level and lives
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


class Level : Widget {
public:
	Level();
	void update(int value);
};


class Lives : Widget {
public:
	Lives();
	void update(int value);
};


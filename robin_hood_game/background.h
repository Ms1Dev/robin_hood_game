#pragma once

#include <fstream>
#include "char2Ansi.h"
#include "config.h"



class Background {
public:
    static Background* getInstance();
    void update(int(&display)[yPixels][xPixels]);
    void right_scroll(int distance);
    void left_scroll(int distance);
    int get_unit_ypos(int heightFromBottom);

private:
    Background();
    static Background* instance;
	int scrollPos = 0;
    struct Dimensions {
        int width, height;
    };
    Dimensions dimensions = {};
    void set_dimensions();
};

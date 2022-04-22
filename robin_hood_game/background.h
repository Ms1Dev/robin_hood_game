#pragma once

#include <fstream>
#include "config.h"

/*
    Singleton class that controls the background
*/


class Background {
public:
    static Background* getInstance();
    ~Background();
    void update(int(&display)[yPixels][xPixels]);
    void right_scroll(int distance);
    void left_scroll(int distance);
    int get_unit_ypos(int heightFromBottom);
    int get_scroll_pos();
    void reset_scroll_pos();

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

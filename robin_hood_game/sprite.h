#pragma once

#include <string>
#include "config.h"
#include "timer.h"
#include "collision_detector.h"

using namespace std;


/*
This is the base class for all moving objects
*/

class Sprite {
private:
    friend class Collision_detector;
    bool isAlive;
protected:
    int x, y, speed, height, width, xrel, collisionMarginX, collisionMarginY;
    string filename;
    string folder;
    Timer* timer = Timer::getInstance();
    Collision_detector* collision_detector = Collision_detector::getInstance();
    bool human;
public:
    bool reverseImage;
    Sprite(int x, int y, int speed, int height, int width, string imageFile);
    bool update(int(&display)[yPixels][xPixels]);
    virtual void animate();
    int get_x();
    int get_y();
    void set_x(int x);
    void set_xrel(int x);
    int get_xrel();
    void set_y(int y);
    int get_height();
    int get_width();
    int get_speed();
    void move_h(bool left = false);
    void move_v(bool up = false);
    int get_xTotal();
};


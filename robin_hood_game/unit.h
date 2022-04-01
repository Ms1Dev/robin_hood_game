#pragma once

#include "sprite.h"


class Unit : public Sprite {
protected:
    int state, animationIndex, animationSpeed;
    unsigned long animationTicks;
    virtual void shoot();
public:
    Unit(int x, int y, int speed);
    void set_state(int state);
    int get_state();
    void walk(bool left = false);
    void stop(bool left = false);
    void kill();
};


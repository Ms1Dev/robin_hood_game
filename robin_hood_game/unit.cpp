#include "unit.h"


Unit::Unit(int x, int y, int speed) :Sprite(x, y, speed, 32, 24, "s0n.txt") {
    state = 0;
    animationIndex = 0;
    animationSpeed = 5;
    animationIndex = 0;
}

bool Unit::update(int(&display)[yPixels][xPixels]) {
    if (state == 2) {
        collisionMarginY = 15;
    }
    else {
        collisionMarginY = 0;
    }
    return __super::update(display);
}

void Unit::walk(bool left) {
    move_h(left);
    reverseImage = left;
    state = 1;
}

void Unit::stop(bool left) {
    state = 0;
    reverseImage = left;
}


void Unit::set_state(int state) {
    this->state = state;
}

int Unit::get_state() {
    return state;
}


void Unit::kill() {
    // if statement to prevent restarting animation if new collision
    if (state != 3) {
        state = 3;
        animationIndex = 0;
        animationTicks = 0;
    }
    doesCollide = false;
}
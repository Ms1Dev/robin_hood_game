#include "unit.h"


Unit::Unit(int x, int y, int speed) :Sprite(x, y, speed, 32, 24, "s0n.txt") {
    state = 0;
    animationIndex = 0;
    animationSpeed = 5;
    animationTicks = 0;
}


void Unit::shoot() {
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

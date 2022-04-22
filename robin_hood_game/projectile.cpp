#include "projectile.h"



Projectile::Projectile(int x, int y, int speed, bool direction, bool human) : Sprite(x, y, speed, 3, 13, "arw.txt") {
    reverseImage = direction;
    this->human = human;
    folder = "arrow/";
    if (reverseImage) {
        this->x -= 10;
    }
    // non human then x position is relative
    if (!human) {
        set_xrel(x - background->get_scroll_pos());
    }
}

// move the projectile on the screen 
bool Projectile::move() {
    bool stillExists = true;
    // move in direction depending on the way projectile image is facing
    move_h(reverseImage);
    // if projectile goes off screen then set exists flag to false
    if (x + xrel + width > xPixels || x + xrel < 0) {
        stillExists = false;
    }
    return stillExists;
}


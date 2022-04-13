#include "projectile.h"



Projectile::Projectile(int x, int y, double speed, bool direction, bool human) : Sprite(x, y, speed, 3, 13, "arw.txt") {
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


bool Projectile::move() {
    bool stillExists = true;
    if (reverseImage) {
        move_h(true);
    }
    else {
        move_h();
    }

    if (x + xrel + width > xPixels || x + xrel < 0) {
        stillExists = false;
    }
    return stillExists;
}


#include "projectile.h"




Projectile::Projectile(int x, int y, double speed, bool direction, bool human) : Sprite(x, y, speed, 3, 13, "arw.txt") {
    reverseImage = direction;
    this->human = human;
    folder = "arrow/";
    if (reverseImage) {
        this->x -= 5;
    }
}


bool Projectile::move() {
    bool stillExists = true;
    if (reverseImage) {
        x -= speed;
    }
    else {
        x += speed;
    }

    if (this->x + width > xPixels || x < 0) {
        destroy();
        stillExists = false;
    }
    return stillExists;
}

void Projectile::destroy() {
    delete this;
}

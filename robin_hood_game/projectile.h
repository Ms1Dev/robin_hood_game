#pragma once

#include "sprite.h"


class Projectile : public Sprite {
public:
    Projectile(int x, int y, int speed, bool direction, bool human);
    ~Projectile() {}
    bool move();
};

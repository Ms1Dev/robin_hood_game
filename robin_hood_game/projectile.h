#pragma once

#include "sprite.h"


class Projectile : public Sprite {
public:
    Projectile(int x, int y, double speed, bool direction, bool human);
    ~Projectile() {}
    bool move();
};

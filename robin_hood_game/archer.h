#pragma once

#include "unit.h"
#include "projectileManager.h"


class Archer : public Unit {
protected:
    ProjectileManager* projectileManager;
    int reloadTime;
    unsigned long reloadTicks;
    void animate();

public:
    Archer(int x, int y, int speed, bool human);
    void shoot();
};


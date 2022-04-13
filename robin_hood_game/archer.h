#pragma once

#include "unit.h"
#include "projectileManager.h"


class Archer : public Unit {
private:
    ProjectileManager* projectileManager;
    int reloadTime;
    unsigned long reloadTicks;
    void animate();

public:
    Archer(int x, int y, int speed, bool human, int lives = 1);
    ~Archer();
    void shoot();
    int* get_livesPtr();
};


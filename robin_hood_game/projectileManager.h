#pragma once

#include "projectile.h"

#define PROJECTILE_MEM_SIZE 10

class ProjectileManager {

private:
    // array of pointers to projectile objects
    Projectile* projectiles[PROJECTILE_MEM_SIZE] = {};
    ProjectileManager() {}
    static ProjectileManager* instance;
public:
    ~ProjectileManager();
    static ProjectileManager* getInstance();
    void add_projectile(Projectile* projectile);
    void update_projectiles(int(&display)[yPixels][xPixels]);
};

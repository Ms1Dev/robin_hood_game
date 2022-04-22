#pragma once

#include "projectile.h"

// maximum projectiles that can be created at any one time
#define PROJECTILE_MEM_SIZE 10

/*
    Singleton class that manages all projectile objects
    By managing this class moves, updates and destroys the projectile objects
    The projectile manager does not instantiate the projectiles - this is done by an archer object
*/

class ProjectileManager {
private:
    // array of pointers to projectile objects
    Projectile* projectiles[PROJECTILE_MEM_SIZE] = {};
    ProjectileManager() {}
    static ProjectileManager* instance;
public:
    void clear();
    static ProjectileManager* getInstance();
    void add_projectile(Projectile* projectile);
    void update_projectiles(int(&display)[yPixels][xPixels]);
};

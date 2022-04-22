#include "projectileManager.h"



ProjectileManager* ProjectileManager::instance = (nullptr);

void ProjectileManager::add_projectile(Projectile* projectile) {
    bool hasSpace = false;
    // iterate over all the slots and add to first empty one
    for (int i = 0; i < PROJECTILE_MEM_SIZE; i++) {
        if (!projectiles[i]) {
            projectiles[i] = projectile;
            hasSpace = true;
            break;
        }
    }
    // if no spaces were found
    if (!hasSpace) {
        throw std::exception("Projectile memory full");
    }
}

void ProjectileManager::update_projectiles(int(&display)[yPixels][xPixels]) {
    // iterate over projectiles and call update func
    for (int i = 0; i < PROJECTILE_MEM_SIZE; i++) {
        bool isDestroyed = false;
        if (projectiles[i]) {
            // update and check if arrow has been destroyed by collision
            isDestroyed = !projectiles[i]->update(display) || !projectiles[i]->move();
        }
        // if the projectile no longer exists then set the dangling pointer to null
        if (isDestroyed) {
            delete projectiles[i];
            projectiles[i] = nullptr;
        }
    }
}

ProjectileManager* ProjectileManager::getInstance() {
    if (!instance) {
        instance = new ProjectileManager;
    }
    return instance;
}

// clear all instances of projectiles from array
void ProjectileManager::clear() {
    for (int i = 0; i < PROJECTILE_MEM_SIZE; i++) {
        if (projectiles[i]) {
            delete projectiles[i];
            projectiles[i] = nullptr;
        }
    }
}
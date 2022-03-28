#include "projectileManager.h"




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
        bool isDangling = false;
        if (projectiles[i]) {
            // add projectile image to display
            projectiles[i]->update(display);
            // move will return false if the projectile is destroyed which will leave the pointer dangling
            isDangling = !projectiles[i]->move();
        }
        // if the projectile no longer exists then set the dangling pointer to null
        if (isDangling) {
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

ProjectileManager* ProjectileManager::instance = (nullptr);


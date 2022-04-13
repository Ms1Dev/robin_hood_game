#include "archer.h"


#define WALKING_ANIMATIONS 3


void Archer::animate() {
    // if archer is not dead (state 3)
    // 3rd character of filename is with or without arrow
    // if archer is reloading n signifies the animation has no arrow
    if (state != 3) {
        if ((*timer).get_ticks() > reloadTicks + reloadTime) {
            filename[2] = 'a';
        }
        else {
            filename[2] = 'n';
        }
    }

    // 2nd character is the frame of the animation and defaults to 0
    filename[1] = '0';

    // depending on the state set the first character of filename which is crouching, standing, walking
    switch (state) {
    // state 0 is standing
    case 0:
        filename[0] = 's';
        break;
    // state 1 is walking
    case 1:
        filename[0] = 'w';
        // use animation ticks to cycle through walking frames
        if ((*timer).get_ticks() > animationTicks + animationSpeed) {
            animationTicks = (*timer).get_ticks();
            animationIndex++;
            if (animationIndex > WALKING_ANIMATIONS - 1) {
                animationIndex = 0;
            }
        }
        // current index + 48 to equal ascii character for that number
        filename[1] = char(animationIndex + 48);
        break;
    // case 2 is crouching
    case 2:
        filename[0] = 'c';
        break;
    // case 3 is dead/dying - animation makes the unit flash several times before disappearing
    case 3:
        filename[0] = 's';
        if ((*timer).get_ticks() > animationTicks + animationSpeed) {
            animationTicks = (*timer).get_ticks();
            if (filename[2] == 'd') {
                filename[2] = 'n';
            }
            else {
                filename[2] = 'd';
                animationIndex++;
            }
            if (animationIndex == 3) {
                isAlive = false;
            }
        }
        break;
    }
}


Archer::Archer(int x, int y, int speed, bool human, int lives) : Unit(x, y, speed, lives) {
    projectileManager = ProjectileManager::getInstance();
    reloadTime = 50;
    reloadTicks = 0;
    if (human) {
        folder = "player/";
    }
    else {
        folder = "archer/";
    }
    collisionMarginX = 8;
    this->human = human;
}


void Archer::shoot() {

    // if archer has reloaded and archer is on screen then shoot
    if (((*timer).get_ticks() > reloadTicks + reloadTime) && state != 1 && x + xrel > 0 && x + xrel < xPixels) {
        reloadTicks = (*timer).get_ticks();

        int arrowOffset = 10 + 5 * state;
        // dynamically create a projectile object
        Projectile* newProjectile = new Projectile(x + 10, y + arrowOffset, 5, reverseImage, human);
        // try to add to projectile manager
        try {
            projectileManager->add_projectile(newProjectile);
        }
        catch (std::exception e) {
            // projectile manager with throw an exception if the array of projectiles is full
            std::cout << e.what();
            // it could not be added to array so delete from memory
            delete newProjectile;
        }
    }
}

int* Archer::get_livesPtr() {
    return &lives;
}

Archer::~Archer() {

}

#pragma once


#include <fstream>
#include "config.h"
#include <cmath>
//#include "projectile.h"
#include "char2Ansi.h"
#include "sprites.h"


void Sprite::update(int(&display)[yPixels][xPixels]) {
    
    // call the child class overriden animation method
    animate();

    int memSize = height * width;

    // allocate memory to put background image
    int* imgData = new int[memSize];

    // load the image from file
    std::ifstream file(filename);
    for (int i = 0; i < height * width; i++) {
        char pixel;
        file >> pixel;
        imgData[i] = cnvrt2ansi(pixel);
    }
    file.close();

    for (int i = 0; i < height; i++) {
        int dy = i + y;
        for (int j = 0; j < width; j++) {
            // 9 is transparent so don't add anything at this pixel
            if (imgData[j + width * i] == 9) {
                continue;
            }
            int dx = j + x;
            display[dy][dx] = imgData[j + width * i];
        }
    }
    delete[] imgData;
}

int Sprite::get_x() {
    return x;
}
int Sprite::get_y() {
    return y;
}
void Sprite::set_x(int x) {
    this->x = x;
}
void Sprite::set_y(int y) {
    this->y = y;
}
int Sprite::get_height() {
    return height;
}
int Sprite::get_width() {
    return width;
}
void Sprite::move_h(bool left) {
    if (left) {
        x -= speed;
    }
    else {
        x += speed;
    }
}
void Sprite::move_v(bool up) {
    if (up) {
        y -= speed;
    }
    else {
        y += speed;
    }
}

// to be overwritten by child classes 
void Sprite::animate(){}



void Unit::shoot() {
    if ((*timer).get_ticks() > reloadTicks + reloadTime) {
        reloadTicks = (*timer).get_ticks();

        int arrowOffset = 10 + 5 * state;
        // dynamically create a projectile object
        Projectile* newProjectile = new Projectile(x + 10, y + arrowOffset, 10);
        // try to add to projectile manager
        try {
            (*this->projectileManager).add_projectile(newProjectile);
        }
        catch (std::exception e) {
            // projectile manager with throw an exception if the array of projectiles is full
            std::cout << e.what();
            // it could not be added to array so delete from memory
            delete newProjectile;
        }
    }
}

void Unit::animate() {
    switch (state) {
    case 0:
        if ((*timer).get_ticks() > reloadTicks + reloadTime) {
            filename = "standing.txt";
        }
        else {
            filename = "standing_shoot.txt";
        }
        break;
    case 1:
        if ((*timer).get_ticks() > animationTicks + animationSpeed) {
            animationTicks = (*timer).get_ticks();
            animationIndex++;
            if (animationIndex >= WALKING_ANIMATIONS) {
                animationIndex = 0;
            }
            filename = animation[animationIndex];
        }
        break;
    case 2:
        if ((*timer).get_ticks() > reloadTicks + reloadTime) {
            filename = "crouch.txt";
        }
        else {
            filename = "crouch_shoot.txt";
        }
        break;
    }
}

void Unit::set_state(int state) {
    this->state = state;
}



bool Projectile::move() {
    bool stillExists = true;
    x += speed;
    if (this->x + width > xPixels) {
        destroy();
        stillExists = false;
    }
    return stillExists;
}

void Projectile::destroy() {
    delete this;
}





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



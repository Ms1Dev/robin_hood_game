#include "collision_detector.h"
#include "sprite.h"

// instance is set to nullptr before object is instantiated 
Collision_detector* Collision_detector::instance(nullptr);

Collision_detector::Collision_detector() {}

// clears all pointers in vector - used when game ends 
void Collision_detector::clearSprites() {
    sprites.clear();
}


Collision_detector* Collision_detector::getInstance() {
    if (!instance) {
        instance = new Collision_detector;
    }
    return instance;
}

// add a pointer to a sprite derived object to the vector
void Collision_detector::addSprite(Sprite* sprite) {
    sprites.push_back(sprite);
}

// removes pointer to sprite from the vector
void Collision_detector::removeSprite(Sprite* sprite) {
    // create iterator 
    vector<Sprite*>::iterator iterator;
    // iterate over all sprites and remove the one that matches the argument
    for (iterator = sprites.begin(); iterator != sprites.end(); ++iterator) {
       if (*iterator == sprite) {
            sprites.erase(iterator);
            break;
       }
    }
}

// iterates over all sprites and checks for a collision
void Collision_detector::detectCollisions() {
    for (int i = 0; i < sprites.size(); i++) {
        // pairs of sprites are checked once hence the j = 1 + i
        for (int j = 1 + i; j < sprites.size(); j++) {
            if (collide(sprites[i], sprites[j])) {
                sprites[i]->kill();
                sprites[j]->kill();
            }
        }
    }
}

// checks if the two sprites passed as arguments are colliding
bool Collision_detector::collide(Sprite* sprite_1, Sprite* sprite_2) {
    Collision_rect rect1(sprite_1);
    Collision_rect rect2(sprite_2);
    return rect1.isColliding(&rect2);
}

// a rectangle that takes attributes from given sprite to use for collision detecting
Collision_detector::Collision_rect::Collision_rect(Sprite* sprite) {
    // collision margins are taken into account - rectangle may be smaller than visible sprite
    x1 = sprite->get_xTotal() + sprite->collisionMarginX;
    y1 = sprite->y + sprite->collisionMarginY;
    x2 = x1 + sprite->width - sprite->collisionMarginX;
    y2 = y1 + sprite->height;
    isHuman = sprite->human;
    doesCollide = sprite->doesCollide;
}

// checks if this rectangle collides with the rectangle passed as an argument
bool Collision_detector::Collision_rect::isColliding(Collision_rect* rect) {

    bool leftCollides = (rect->x1 >= x1 && rect->x1 <= x2);
    bool rightCollides = (rect->x2 >= x1 && rect->x2 <= x2);

    bool topCollides = (rect->y1 >= y1 && rect->y1 <= y2);
    bool bottomCollides = (rect->y2 >= y1 && rect->y2 <= y2);

    return (leftCollides || rightCollides) && (topCollides || bottomCollides) && rect->isHuman != isHuman && rect->doesCollide && doesCollide;
}
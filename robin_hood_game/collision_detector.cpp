#include "collision_detector.h"
#include "sprite.h"


Collision_detector* Collision_detector::instance(nullptr);


Collision_detector::Collision_detector() {

}

Collision_detector::~Collision_detector() {

}



Collision_detector* Collision_detector::getInstance() {
    if (!instance) {
        instance = new Collision_detector;
    }
    return instance;
}

void Collision_detector::addSprite(Sprite* sprite) {
    sprites.push_back(sprite);
}

void Collision_detector::removeSprite(Sprite* sprite) {

    vector<Sprite*>::iterator iterator;

    for (iterator = sprites.begin(); iterator != sprites.end(); ++iterator) {
       if (*iterator == sprite) {
            sprites.erase(iterator);
            break;
       }
    }
}


void Collision_detector::detectCollisions() {
    for (int i = 0; i < sprites.size(); i++) {
        for (int j = 1 + i; j < sprites.size(); j++) {
            if (collide(sprites[i], sprites[j])) {
                // TODO 
                sprites[i]->kill();
                sprites[j]->kill();
            }
        }
    }
}


bool Collision_detector::collide(Sprite* sprite_1, Sprite* sprite_2) {
    Collision_rect rect1(sprite_1);
    Collision_rect rect2(sprite_2);
    return rect1.isColliding(&rect2);
}



Collision_detector::Collision_rect::Collision_rect(Sprite* sprite) {
    x1 = sprite->get_xTotal() + sprite->collisionMarginX;
    y1 = sprite->y + sprite->collisionMarginY;
    x2 = x1 + sprite->width - sprite->collisionMarginX;
    y2 = y1 + sprite->height;
    isHuman = sprite->human;
    doesCollide = sprite->doesCollide;
}


bool Collision_detector::Collision_rect::isColliding(Collision_rect* rect) {

    bool leftCollides = (rect->x1 >= x1 && rect->x1 <= x2);
    bool rightCollides = (rect->x2 >= x1 && rect->x2 <= x2);

    bool topCollides = (rect->y1 >= y1 && rect->y1 <= y2);
    bool bottomCollides = (rect->y2 >= y1 && rect->y2 <= y2);

    return (leftCollides || rightCollides) && (topCollides || bottomCollides) && rect->isHuman != isHuman && rect->doesCollide && doesCollide;
}
#include "sprite.h"
#include <fstream>
#include "char2Ansi.h"


Sprite::Sprite(int x, int y, int speed, int height, int width, string imageFile) {
    isAlive = true;
    doesCollide = true;
    this->x = x;
    xrel = 0;
    this->y = y;
    this->speed = speed;
    this->height = height;
    this->width = width;
    reverseImage = false;
    folder = "archer/";
    filename = imageFile;
    collision_detector->addSprite(this);
    collisionMarginX = 0;
    collisionMarginY = 0;
}


bool Sprite::update(int(&display)[yPixels][xPixels]) {

    // non human then x position is relative
    if (!human) {
        set_xrel(x - background->get_scroll_pos());
    }

    // call the child class overriden animation method
    animate();

    int memSize = height * width;

    // allocate memory to put background image
    int* imgData = new int[memSize];

    string fn = "images/" + folder + filename;

    // load the image from file
    std::ifstream file(fn);
    for (int i = 0; i < memSize; i++) {
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
            int dx;
            if (reverseImage) {
                dx = width - j + xrel + x;
            }
            else {
                dx = j + xrel + x;
            }
            if (dx < xPixels && dx > 0) {
                display[dy][dx] = imgData[j + width * i];
            }
        }
    }
    delete[] imgData;

    return isAlive;
}

int Sprite::get_x() {
    return x;
}
int Sprite::get_xrel() {
    return xrel;
}
int Sprite::get_xCombined() {
    return x + background->get_scroll_pos();
}
int Sprite::get_xTotal() {
    return xrel + x;
}
int Sprite::get_y() {
    return y;
}
void Sprite::set_x(int x) {
    this->x = x;
}
void Sprite::set_xrel(int x) {
    xrel = x;
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
int Sprite::get_speed() {
    return speed;
}
void Sprite::move_h(bool left) {
    if (left) {
        x -= speed + (speed * human);
    }
    else {
        x += speed + (speed * human);
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
void Sprite::animate() {}


void Sprite::kill() {
    doesCollide = false;
    isAlive = false;
}

Sprite::~Sprite() {
    collision_detector->removeSprite(this);
}
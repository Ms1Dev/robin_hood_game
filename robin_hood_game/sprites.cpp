#include <fstream>
#include "config.h"
#include <cmath>
#include "char2Ansi.h"
#include "sprites.h"
#include <string>



Sprite::Sprite(int x, int y, int speed, int height, int width, string imageFile) {
    this->x = x;
    xrel = 0;
    this->y = y;
    this->speed = speed;
    this->height = height;
    this->width = width;
    reverseImage = false;
    folder = "archer/";
    filename = imageFile;
    //set_filename(imageFile);
}

void Sprite::set_filename(string filename) {
    // sets the initial filename used for sprite image
    if (filename.length() > 7) {
        // TODO sort this out
        throw "File name too long";
    }
    else {
        for (int i = 0; i < 8; i++) {
            if (i >= filename.length()) {
                filename[i] = '\0';
                continue;
            }
            this->filename[i] = filename[i];
        }
    }
}

void Sprite::update(int(&display)[yPixels][xPixels]) {
    
    // call the child class overriden animation method
    animate();

    int memSize = height * width;

    // allocate memory to put background image
    int* imgData = new int[memSize];
       
    string fn = "images/" + folder + filename;

    // load the image from file
    std::ifstream file(fn);
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
}

int Sprite::get_x() {
    return x;
}
int Sprite::get_xrel() {
    return xrel;
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



Unit::Unit(int x, int y, int speed) :Sprite(x, y, speed, 32, 24, "s0n.txt") {
    state = 0;
    animationIndex = 0;
    animationSpeed = 5;
    animationTicks = 0;
}


void Unit::set_state(int state) {
    this->state = state;
}


void Archer::animate() {
    // TODO comment
    if ((*timer).get_ticks() > reloadTicks + reloadTime) {
        filename[2] = 'a';
    }
    else {
        filename[2] = 'n';
    }
    // default the animation to 0
    filename[1] = '0';

    switch (state) {
        case 0:
            filename[0] = 's';
            break;
        case 1:
            filename[0] = 'w';
            if ((*timer).get_ticks() > animationTicks + animationSpeed) {
                animationTicks = (*timer).get_ticks();
                animationIndex++;
                if (animationIndex > WALKING_ANIMATIONS - 1) {
                    animationIndex = 0;
                }
            }
            filename[1] = char(animationIndex + 48);
            break;
        case 2:
            filename[0] = 'c';
            break;
    }
}

Archer::Archer(int x, int y, int speed) : Unit(x, y, speed) {
    projectileManager = ProjectileManager::getInstance();
    reloadTime = 50;
    reloadTicks = 0;
    folder = "archer/";
}


void Archer::shoot() {
    if (((*timer).get_ticks() > reloadTicks + reloadTime) && state != 1) {
        reloadTicks = (*timer).get_ticks();

        int arrowOffset = 10 + 5 * state;
        // dynamically create a projectile object
        // TODO: rename reverse image
        Projectile* newProjectile = new Projectile(x + 10, y + arrowOffset, 10, reverseImage);
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


Player::Player(int x, int y, int speed) : Archer(x, y, speed) {
    folder = "player/";
}


Projectile::Projectile(int x, int y, double speed, bool direction) : Sprite(x, y, speed, 3, 13, "arw.txt") {
    reverseImage = direction;
    folder = "arrow/";
    if (reverseImage) {
        this->x -= 5;
    }
}


bool Projectile::move() {
    bool stillExists = true;
    if (reverseImage) {
        x -= speed;
    }
    else {
        x += speed;
    }
    
    if (this->x + width > xPixels || x < 0) {
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

ProjectileManager* ProjectileManager::getInstance() {
    if (!instance) {
        instance = new ProjectileManager;
    }
    return instance;
}

ProjectileManager* ProjectileManager::instance = (nullptr);


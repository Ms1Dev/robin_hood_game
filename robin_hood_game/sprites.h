#pragma once
#include <fstream>
#include "config.h"
#include <cmath>
#include <iostream>
#include "timer.h"


using namespace std;

#define PROJECTILE_MEM_SIZE 10
#define WALKING_ANIMATIONS 4


class Sprite {
public:
    int x, y, speed, height, width;
    const char* filename;

    Sprite(int x, int y, int speed, int height, int width, const char* filename) {
        this->x = x;
        this->y = y;
        this->speed = speed;
        this->height = height;
        this->width = width;
        this->filename = filename;
        animationTicks = 0;
    }
    Timer* timer = Timer::getInstance();
    unsigned long animationTicks;
    void update(int(&display)[yPixels][xPixels]);
    virtual void animate();
    int get_x();
    int get_y();
    void set_x(int x);
    void set_y(int y);
    int get_height();
    int get_width();
    int get_speed();
    void move_h(bool left = false);
    void move_v(bool up = false);

};




class Projectile : public Sprite {
public:
    Projectile(int x, int y, double speed) : Sprite(x,y,speed,3,13,"arrow.txt") {}
    ~Projectile() {}
    bool move();
    void destroy();
};



class ProjectileManager {

private:
    // array of pointers to projectile objects
    Projectile* projectiles[PROJECTILE_MEM_SIZE] = {};
    ProjectileManager() {}
    static ProjectileManager* instance;
public:
    
    static ProjectileManager* getInstance();
    void add_projectile(Projectile* projectile);
    void update_projectiles(int(&display)[yPixels][xPixels]);
};





class Unit : public Sprite {
private:
    ProjectileManager* projectileManager;
    void animate();
    int state, animationIndex, animationSpeed, reloadTime;
    unsigned long reloadTicks;
    const char* animation[WALKING_ANIMATIONS] = { "walking_1.txt", "walking_2.txt", "walking_3.txt", "walking_4.txt" };
public:

    Unit(int x, int y, int speed) :Sprite(x, y, speed, 32, 24, "standing.txt") {
        projectileManager = ProjectileManager::getInstance();
        state = 0;
        animationIndex = 0;
        animationSpeed = 5;
        reloadTime = 50;
        reloadTicks = 0;
    }
    void shoot();
    void set_state(int state);
};


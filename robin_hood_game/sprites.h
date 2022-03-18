#pragma once
#include <fstream>
#include "config.h"
#include <cmath>
#include <iostream>
#include "timer.h"


using namespace std;

#define PROJECTILE_MEM_SIZE 10
#define WALKING_ANIMATIONS 3


class Sprite {
public:
    int x, y, speed, height, width, xrel;
    
    bool reverseImage;
    string filename;
    string folder;
    Timer* timer = Timer::getInstance();

    Sprite(int x, int y, int speed, int height, int width, string imageFile);
    void update(int(&display)[yPixels][xPixels]);
    virtual void animate();
    int get_x();
    int get_y();
    void set_x(int x);
    void set_xrel(int x);
    int get_xrel();
    void set_y(int y);
    int get_height();
    int get_width();
    int get_speed();
    void move_h(bool left = false);
    void move_v(bool up = false);
    void set_filename(string filename);
};



class Projectile : public Sprite {
public:
    Projectile(int x, int y, double speed, bool direction);
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
protected:    
    int state, animationIndex, animationSpeed;
    unsigned long animationTicks;
public:
    Unit(int x, int y, int speed);
    void set_state(int state);
};



class Archer : public Unit {
protected:
    ProjectileManager* projectileManager;
    int reloadTime;
    unsigned long reloadTicks;
    void animate();
public:
    Archer(int x, int y, int speed);
    void shoot();
};



class Player : public Archer {
public:
    Player(int x, int y, int speed);
};


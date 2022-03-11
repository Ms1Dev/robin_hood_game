#pragma once
#include <fstream>
#include "config.h"
#include <cmath>
#include "projectile.h"
#include "char2Ansi.h"

struct Coord {
    int x;
    int y;
};

class Unit {
private:
    int x, y, speed;
    int graphic[32][24] = {};
    int height = sizeof(graphic) / sizeof(graphic[0]);
    int width = sizeof(graphic[0]) / sizeof(graphic[0][0]);
    ProjectileManager* projectileManager;

public:
    string output = "";
    Unit(int x, int y, int speed, ProjectileManager* projMan) {
        this->x = x;
        this->y = y;
        this->speed = speed;
        projectileManager = projMan;
        set_graphic();
    }
    void set_graphic() {
        // load the image from file
        std::ifstream file("standing.txt");
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                char pixel;
                file >> pixel;
                graphic[i][j] = cnvrt2ansi(pixel);
            }
        }
        file.close();
    }

    void shoot() {
        // dynamically create a projectile object
        Projectile* newProjectile = new Projectile(x, y + 10, 10);
        // try to add to projectile manager
        try {
            (*this->projectileManager).add_projectile(newProjectile);
        }
        catch (std::exception e) {
            // projectile manager with throw an exception if the array of projectiles is full
            std::cout << e.what();
            newProjectile->destroy();
        }
    }

    int get_x() {
        return x;
    }
    int get_y() {
        return y;
    }
    void set_x(int x) {
        this->x = x;
    }
    void set_y(int y) {
        this->y = y;
    }
    int get_height() {
        return height;
    }
    int get_width() {
        return width;
    }
    void move_h(bool left = false) {
        if (left) {
            x -= speed;
        }
        else {
            x += speed;
        }
    }
    void move_v(bool up = false) {
        if (up) {
            y -= speed;
        }
        else {
            y += speed;
        }
    }


    void update(int(&display)[yPixels][xPixels]) {

        // add graphic to the display matrix
        for (int i = 0; i < height; i++) {
            int dy = i + y;
            for (int j = 0; j < width; j++) {
                // 9 is transparent so don't add anything at this pixel
                if (graphic[i][j] == 9) {
                    continue;
                }
                int dx = j + x;
                display[dy][dx] = graphic[i][j];
            }
        }

    }
};



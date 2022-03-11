#pragma once

#include "char2Ansi.h"

#define PROJECTILE_MEM_SIZE 10


class Projectile {
private:
    int x, y;
    double velocity, angle;
    int graphic[3][13] = {};
    int height = sizeof(graphic) / sizeof(graphic[0]);
    int width = sizeof(graphic[0]) / sizeof(graphic[0][0]);
    ~Projectile() {
        std::cout << "destroyed";
    }
    void set_graphic() {
        // load the image from file
        std::ifstream file("arrow.txt");
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                char pixel;
                file >> pixel;
                graphic[i][j] = cnvrt2ansi(pixel);
            }
        }
        file.close();
    }

public:
    Projectile(int x, int y, double velocity) {
        this->x = x;
        this->y = y;
        this->velocity = velocity;
        std::cout << "created";
        set_graphic();
    }
    void set_x(int x) {
        this->x = x;
    }
    void set_y(int y) {
        this->y = y;
    }
    int get_x() {
        return x;
    }
    int get_y() {
        return y;
    }
    void destroy() {
        delete this;
    }
    bool update(int(&display)[yPixels][xPixels]) {
        bool stillExists = true;
        x += velocity;
        if (this->x > xPixels) {
            destroy();
            stillExists = false;
        }
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
        return stillExists;
    }
};



class ProjectileManager {

private:
    // array of pointers to projectile objects
    Projectile* projectiles[PROJECTILE_MEM_SIZE] = {};

public:
    ProjectileManager() {

    }

    void add_projectile(Projectile* projectile) {
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

    void update_projectiles(int(&display)[yPixels][xPixels]) {
        // iterate over projectiles and call update func
        for (int i = 0; i < PROJECTILE_MEM_SIZE; i++) {
            bool isDangling = false;
            if (projectiles[i]) {
                // update will return true if the projectile still exists
                isDangling = !projectiles[i]->update(display);
            }
            // if the projectile doesn't exist then set the dangling pointer to null
            if (isDangling) {
                projectiles[i] = nullptr;
            }
        }
    }

};





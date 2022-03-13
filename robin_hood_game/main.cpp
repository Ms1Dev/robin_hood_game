#include <iostream> 
#include "display.h"
#include "timer.h"
#include "background.h"
#include "sprites.h"

using namespace std;

// create projectile manager singleton
ProjectileManager* projectileManager = ProjectileManager::getInstance();

// create background singleton
Background* background = Background::getInstance();

// if height of screen changes keep the units y position relative to bottom of background
int unitYpos = (*background).get_unit_ypos(36);

Unit unit(10, unitYpos, 2);

// declare function that updates the system
void update();

int main()
{
    // timer object for controlling frame rates and timing operations
    Timer* timer = Timer::getInstance();
    // pass reference to function that is called on every tick
    (*timer).on_tick(&update);
    // uses windows.h to apply settings to console window for better gameplay
    configure_console();
    // game loop
    while (true) {
        (*timer).run();
    }
}


void update() {
    // update the background
    (*background).update(display);
    
    // update projectiles
    (*projectileManager).update_projectiles(display);

    // update units
    unit.update(display);

    // print the display to the console
    draw();

    // set unit state to standing TODO: move to unit class
    unit.set_state(0);
    // get key input
    if ((GetKeyState(37) & 0x8000) && (unit.get_x() > 0)) {
        if (unit.get_x() > 10) {
            unit.move_h(true);
        }
        else {
            (*background).right_scroll(2);
        }
        unit.set_state(1);
    }
    else if ((GetKeyState(39) & 0x8000)) {
        if (unit.get_x() < xPixels / 2) {
            unit.move_h();
        }
        else {
            (*background).left_scroll(2);
        }  
        unit.set_state(1);
    }
    else if ((GetKeyState(40) & 0x8000)) {
        //unit.move_h();
        unit.set_state(2);
    }

    if (GetKeyState(32) & 0x8000) {
        unit.shoot();
    }
}
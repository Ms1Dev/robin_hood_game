#include <iostream> 
#include "display.h"
#include "timer.h"
#include "background.h"
#include "projectileManager.h"
#include "archer.h"
#include "controller.h"
#include "computer.h"


using namespace std;

// create projectile manager singleton
ProjectileManager* projectileManager = ProjectileManager::getInstance();

// create background singleton
Background* background = Background::getInstance();

Collision_detector* collision_detector = Collision_detector::getInstance();

// if height of screen changes keep the units y position relative to bottom of background
int unitYpos = (*background).get_unit_ypos(36);

Archer player(10, unitYpos, 1, true);

Controller human(&player);

Computer computer(&player, unitYpos);

// declare function that updates the system
bool update();

int main()
{
    // set the random seed used in other files
    srand(time(0));

    computer.newInstance();
        
    // timer object for controlling frame rates and timing operations
    Timer* timer = Timer::getInstance();
    // pass reference to function that is called on every tick
    (*timer).on_tick(&update);
    // uses windows.h to apply settings to console window for better gameplay
    configure_console();
    // game loop




    bool run = true;

    while (run) {
        run = (*timer).run();
    }

  
    return 0;
}


bool update() {
    // update the background image
    (*background).update(display);
    
    // update projectiles
    (*projectileManager).update_projectiles(display);

    // read inputs from key presses
    human.command_update();

    // update player images
    bool run = player.update(display);

    // update all computer controlled units
    computer.update(display);

    // detect collisions between sprites
    collision_detector->detectCollisions();

    // print the display to the console
    draw();

    return run;
}
#include <iostream> 
#include "display.h"
#include "timer.h"
#include "background.h"
#include "projectileManager.h"
#include "archer.h"
#include "controller.h"


using namespace std;

// create projectile manager singleton
ProjectileManager* projectileManager = ProjectileManager::getInstance();

// create background singleton
Background* background = Background::getInstance();

Collision_detector* collision_detector = Collision_detector::getInstance();

// if height of screen changes keep the units y position relative to bottom of background
int unitYpos = (*background).get_unit_ypos(36);

Archer player(10, unitYpos, 2, true);

Controller human(&player);

Archer* archer = new Archer(50, unitYpos, 1, false);

Archer_controller comp(archer, &player);

// declare function that updates the system
void update();

int main()
{
    archer->reverseImage = true;
        
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

    human.command_update();

    comp.command_update();

    collision_detector->detectCollisions();

    // update units
    player.update(display);
    
    // move other archer relative to background
    // TODO: move into archer class somehow or enemy controller
    archer->set_xrel(archer->get_x() - background->get_scroll_pos());

    archer->update(display);

    // print the display to the console
    draw();
}
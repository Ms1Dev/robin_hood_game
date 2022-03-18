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

Player player(10, unitYpos, 2);

Archer* archer = new Archer(50, unitYpos, 2);


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

    // update units
    player.update(display);
    
    // move other archer relative to background
    // TODO: move into archer class somehow or enemy controller
    archer->set_xrel(archer->get_x() - background->get_scroll_pos());

    archer->update(display);

    // print the display to the console
    draw();

    // set player state to standing TODO: move to player class
    player.set_state(0);
    // get key input
    if ((GetKeyState(37) & 0x8000) && (player.get_x() > 0)) {
        if (player.get_x() > 10) {
            player.move_h(true);
            player.reverseImage = true;
        }
        else {
            (*background).right_scroll(2);
        }
        player.set_state(1);
    }
    else if ((GetKeyState(39) & 0x8000)) {
        if (player.get_x() < xPixels / 2) {
            player.move_h();
            player.reverseImage = false;
        }
        else {
            (*background).left_scroll(2);
        }  
        player.set_state(1);
    }
    else if ((GetKeyState(40) & 0x8000)) {
        //player.move_h();
        player.set_state(2);
    }

    if (GetKeyState(32) & 0x8000) {
        player.shoot();
    }
}
#include "game.h"



Game::Game() : 
player(10, unitYpos, 1, true),
human(&player),
computer(&player, unitYpos)
{
    computer.newInstance();
}


bool Game::update() {
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
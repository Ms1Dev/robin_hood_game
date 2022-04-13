#include "game.h"
#include <fstream>
#include <iostream>


Game::Game() : 
player(10, unitYpos, 1, true, 3),
human(&player, 500),
computer(&player, unitYpos)
{
    level = readLevel();
    computer.newInstance();
    lives = player.get_livesPtr();
}

// get the current level from file
int Game::readLevel() {
    int lvl = 1;

    std::ifstream file("data/level.txt");
    // if no file then level is 1
    if (file) {
        while (!file.eof()) {
            file >> lvl;
        }
    }
    file.close();

    return lvl;
}

// writes the current level to file - creates file if doesnt exist
void Game::writeLevel(int level) {
    std::fstream file;
    file.open("data/level.txt", ios::out);
    file << level;
    file.close();
}


int Game::getLevel() {
    return level;
}

int* Game::getlivesPtr() {
    return lives;
}

// updates objects in game
// returns false when game ends
// is called by timer object 
bool Game::update() {

    // update the background image
    (*background).update(display);

    // update projectiles
    (*projectileManager).update_projectiles(display);

    // update player images
    bool run = player.update(display);

    // read inputs from key presses
    gameWon = human.command_update();

    // update all computer controlled units
    computer.update(display);

    // detect collisions between sprites
    collision_detector->detectCollisions();

    // print the display to the console
    draw();

    return run && !gameWon;
}

// game destructor
// clear singleton data and write level to file
Game::~Game() {
    if (gameWon) {
        writeLevel(level + 1);
    }
    else {
        writeLevel(1);
    }
    background->reset_scroll_pos();
    projectileManager->clear();
    collision_detector->clearSprites();
}
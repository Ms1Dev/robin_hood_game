#pragma once

#include <iostream> 
#include "display.h"
#include "timer.h"
#include "background.h"
#include "projectileManager.h"
#include "archer.h"
#include "controller.h"
#include "computer.h"
#include "header.h"

// container object for most of the objects used in the game
// is destroyed on ending the level/game
class Game {
private:
	ProjectileManager* projectileManager = ProjectileManager::getInstance();
	Background* background = Background::getInstance();
	Collision_detector* collision_detector = Collision_detector::getInstance();
	int unitYpos = (*background).get_unit_ypos(36);
	Archer player;
	Controller human;
	Computer computer;
	int level;
	int* lives;
	static int readLevel();
	static void writeLevel(int level);
	bool gameWon = false;
public:
	Game();
	~Game();
	bool update();
	int getLevel();
	int* getlivesPtr();
};


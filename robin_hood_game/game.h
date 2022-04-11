#pragma once

#include <iostream> 
#include "display.h"
#include "timer.h"
#include "background.h"
#include "projectileManager.h"
#include "archer.h"
#include "controller.h"
#include "computer.h"

class Game {
private:
	ProjectileManager* projectileManager = ProjectileManager::getInstance();
	Background* background = Background::getInstance();
	Collision_detector* collision_detector = Collision_detector::getInstance();
	int unitYpos = (*background).get_unit_ypos(36);;
	Archer player;
	Controller human;
	Computer computer;
public:
	Game();
	bool update();
};


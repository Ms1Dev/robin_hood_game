#pragma once

#include "background.h"
#include "archer.h"
#include <Windows.h>
#include "timer.h"


/*
	This controller object takes input from the user as keypresses and controls the player unit
*/

class Controller {
public:
	Controller(Archer* player, int mapSize = 0);
	bool command_update();
protected:
	int mapSize;
	Timer* timer = Timer::getInstance();
	Archer* player;
	Background* background = Background::getInstance();
};


/*
	Controller for computer controlled archers
	Inherits from controller and adds basic AI for controlling units
*/


class Archer_controller : public Controller {
public:
	Archer_controller(Archer* archer, Archer* player);
	void command_update();
private:
	Archer* thisUnit;
	int retreatDistance, attackDistance, state, shootDelay;
	unsigned long shootTicks = 0;
};



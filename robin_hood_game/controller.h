#pragma once

#include "background.h"
#include "archer.h"
#include <Windows.h>
#include "timer.h"


class Controller {
public:
	Controller(Archer* player);
	void command_update();
protected:
	Timer* timer = Timer::getInstance();
	Archer* player;
	Background* background = Background::getInstance();
};




class Archer_controller : public Controller {
public:
	Archer_controller(Archer* archer, Archer* player);
	void command_update();
private:
	Archer* thisUnit;
	int retreatDistance, attackDistance, state, shootDelay;
	unsigned long shootTicks = 0;
};



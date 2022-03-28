#pragma once

#include "background.h"
#include "archer.h"
#include <Windows.h>


class Controller {
public:
	Controller(Archer* player);
	void command_update();
protected:
	Archer* player;
	Background* background = Background::getInstance();
};




class Archer_controller : public Controller {
public:
	Archer_controller(Archer* archer, Archer* player);
	void command_update();
private:
	Archer* thisUnit;
	int retreatDistance, attackDistance, state;
};



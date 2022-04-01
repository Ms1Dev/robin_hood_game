#pragma once

#include <list>
#include "config.h"

class Archer;
class Archer_controller;

class Computer{
private:
	Archer* player;
	struct Archer_Instance {
		Archer* archer;
		Archer_controller* controller;
	};
	int unitYpos;
	std::list<Archer_Instance*> archerUnits();
public:
	Computer(Archer* player, int unitYpos);
	void update(int(&display)[yPixels][xPixels]);
	void newInstance();
};


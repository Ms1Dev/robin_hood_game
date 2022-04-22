#pragma once

#include <list>
#include "config.h"
#include "timer.h"


// declare these classes for use in Computer declaration
class Archer;
class Archer_controller;

/*
	This object represents the computer player
	It holds a list of all archer instances and updates them
	An archer instance is the archer object and the archer_controller for that archer stored in a struct
*/


class Computer{
private:
	Archer* player;

	struct Archer_Instance {
		Archer* archer;
		Archer_controller* controller;
	};

	int unitYpos;
	std::list<Archer_Instance> archerUnits;
	Timer* timer = Timer::getInstance();
	unsigned long spawnTicks = 0;
	int spawnDelayLimit[2] = {50, 200};
	int spawnDelay;
	int unitLimit = 2;
public:
	Computer(Archer* player, int unitYpos);
	~Computer();
	void update(int(&display)[yPixels][xPixels]);
	void newInstance();
	void setUnitLimit(int limit);
	void setSpawnDelayLimit(int lowerLimit, int upperLimit);
};


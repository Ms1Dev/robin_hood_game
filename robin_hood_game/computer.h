#pragma once

#include <list>
#include "config.h"
#include "timer.h"

// pre declare classes used for this declaration
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


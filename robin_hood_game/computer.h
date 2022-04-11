#pragma once

#include <list>
#include "config.h"
#include "timer.h"


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
	int spawnDelayLimit[2] = {200, 300};
	int spawnDelay;
public:
	Computer(Archer* player, int unitYpos);
	~Computer();
	void update(int(&display)[yPixels][xPixels]);
	void newInstance();
};


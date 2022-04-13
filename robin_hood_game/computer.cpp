#include "computer.h"
#include "archer.h"
#include "controller.h"
#include <time.h>


Computer::Computer(Archer* player, int unitYpos) {
	this->player = player;
	this->unitYpos = unitYpos;
	spawnTicks = timer->get_ticks();
	// set the initial spawn delay
	spawnDelay = rand() % (spawnDelayLimit[1] - spawnDelayLimit[0]) + spawnDelayLimit[0];
}


Computer::~Computer() {
	// create an iterator for the while loop
	std::list<Archer_Instance>::iterator iterator = archerUnits.begin();
	// delete all instances in list
	while (iterator != archerUnits.end()) {
		delete iterator->controller;
		delete iterator->archer;
		archerUnits.erase(iterator++);
	}
}

void Computer::newInstance() {
	Archer* newArcher = new Archer(player->get_xCombined() + 100, unitYpos, 1, false);
	Archer_controller* controller = new Archer_controller(newArcher, player);

	Archer_Instance instance{
		newArcher,
		controller
	};

	archerUnits.push_back(instance);
}


void Computer::update(int(&display)[yPixels][xPixels]) {

	// create an iterator for the while loop
	std::list<Archer_Instance>::iterator iterator = archerUnits.begin();

	while (iterator != archerUnits.end()) {

		iterator->controller->command_update();

		// if update returns false (archer is not alive) then delete
		if (!iterator->archer->update(display)) {
			delete iterator->controller;
			delete iterator->archer;
			archerUnits.erase(iterator++);
		}
		else {
			iterator++;
		}
	}

	if (spawnTicks + spawnDelay < timer->get_ticks()) {
		// get a new random delay value
		spawnDelay = rand() % (spawnDelayLimit[1] - spawnDelayLimit[0]) + spawnDelayLimit[0];
		// reset the timer
		spawnTicks = timer->get_ticks();

		if (archerUnits.size() < 4) {
			newInstance();
		}
	}

}
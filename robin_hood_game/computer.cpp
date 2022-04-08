#include "computer.h"
#include "archer.h"
#include "controller.h"



Computer::Computer(Archer* player, int unitYpos) {
	this->player = player;
	this->unitYpos = unitYpos;
}


void Computer::newInstance() {
	Archer* newArcher = new Archer(50, unitYpos, 1, false);
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

}
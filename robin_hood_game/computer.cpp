#include "computer.h"

#include "archer.h"
#include "controller.h"



Computer::Computer(Archer* player, int unitYpos) {
	this->player = player;
	this->unitYpos = unitYpos;
}


void Computer::newInstance() {
	Archer* newArcher = new Archer(50, unitYpos, 1, false);
	Archer_controller* controller = new Archer_controller(player, newArcher);

	Archer_Instance instance{
		newArcher,
		controller
	};

	archerUnits.push_back(&instance);
}


void Computer::update(int(&display)[yPixels][xPixels]) {

	std::list<Archer_Instance>::iterator iterator;

	/*for( iterator = archerUnits.begin(); iterator != archerUnits.end(); ++iterator){
		iterator->controller->command_update();
		iterator->archer->update(display);
	}*/

}
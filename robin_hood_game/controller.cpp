#include "controller.h"


Controller::Controller(Archer* player) {
	this->player = player;
}

void Controller::command_update() {
    player->set_state(0);
    // get key input
    if ((GetKeyState(37) & 0x8000) && (player->get_x() > 0)) {
        if (player->get_x() > 10) {
            player->walk(true);
        }
        else {
            (*background).right_scroll(2);
            player->set_state(1);
        }
    }
    else if ((GetKeyState(39) & 0x8000)) {
        if (player->get_x() < xPixels / 2) {
            player->walk();
        }
        else {
            (*background).left_scroll(2);
            player->set_state(1);
        }
    }
    else if ((GetKeyState(40) & 0x8000)) {
        player->set_state(2);
    }

    if (GetKeyState(32) & 0x8000 && player->get_state() != 2) {
        player->shoot();
    }
}




Archer_controller::Archer_controller(Archer* archer, Archer* player) : Controller::Controller(player) {
	thisUnit = archer;
    retreatDistance = 60;
    attackDistance = 110;
    // state: 0 = standing, 1 = walk left, 2 = walk right
    state = 0;
}



void Archer_controller::command_update() {
    int distanceToPlayer = thisUnit->get_xTotal() - player->get_x();
    int midDistance = retreatDistance + ((attackDistance - retreatDistance) / 2);
    
    if (state == 0 && distanceToPlayer < retreatDistance) {
        state = 2;
    }
    if (state == 0 && distanceToPlayer > attackDistance) {
        state = 1;
    }
    if (state == 2 && distanceToPlayer > midDistance) {
        state = 0;
    }
    if (state == 1 && distanceToPlayer < midDistance) {
        state = 0;
    }

    switch (state) {
    case 1:
        thisUnit->walk(true);
        break;
    case 2:
        thisUnit->walk();
        break;
    default:
        thisUnit->stop(true);
        break;
    }
}
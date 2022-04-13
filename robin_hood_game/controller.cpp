#include "controller.h"
#include <time.h>


Controller::Controller(Archer* player, int mapSize) {
	this->player = player;
    this->mapSize = mapSize;
}

bool Controller::command_update() {
    // if player is dead do not continue
    if (player->get_state() == 3) {
        return false;
    }

    player->set_state(0);
    
    // left arrow key pressed
    if ((GetKeyState(37) & 0x8000) && (player->get_x() > 0)) {
        if (player->get_x() > 10) {
            player->walk(true);
        }
        else {
            (*background).right_scroll(2);
            player->set_state(1);
        }
    }
    // right arrow key
    else if ((GetKeyState(39) & 0x8000)) {
        if (player->get_x() < xPixels / 2 - 20 || background->get_scroll_pos() > mapSize) {
            player->walk();
        }
        else {
            (*background).left_scroll(2);
            player->set_state(1);
        }
    }
    // down arrow key
    else if ((GetKeyState(40) & 0x8000)) {
        player->set_state(2);
    }
    // space bar
    if (GetKeyState(32) & 0x8000 && player->get_state() != 2) {
        player->shoot();
    }

    return player->get_x() + player->get_width() >= xPixels;
}




Archer_controller::Archer_controller(Archer* archer, Archer* player) : Controller::Controller(player) {
	thisUnit = archer;
    // generate random attack and retreat distances so units dont stack on top of eachother
    retreatDistance = rand() % 40 + 30;
    attackDistance = rand() % 40 + 90;
    // state: 0 = standing, 1 = walk left, 2 = walk right
    state = 0;

    shootDelay = rand() % 30 + 30;
}


void Archer_controller::command_update() {
    // if unit is dead do not continue
    if (thisUnit->get_state() == 3) {
        return;
    }
    // calculate distances from player
    int distanceToPlayer = thisUnit->get_xTotal() - player->get_x();
    int midDistance = retreatDistance + ((attackDistance - retreatDistance) / 2);
    // if player is closer than retreat distance then walk right
    if (state == 0 && distanceToPlayer < retreatDistance) {
        state = 2;
    }
    // if player is further than attack distance then walk left
    if (state == 0 && distanceToPlayer > attackDistance) {
        state = 1;
    }
    // if walking right stop midway between attack and retreat distances
    if (state == 2 && distanceToPlayer > midDistance) {
        state = 0;
    }
    // same as above but walking left
    if (state == 1 && distanceToPlayer < midDistance) {
        state = 0;
    }

    // convert state into action
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

    if (shootTicks + shootDelay < timer->get_ticks()) {
        shootTicks = timer->get_ticks();
        shootDelay = rand() % 30 + 30;
        thisUnit->shoot();
    }
}
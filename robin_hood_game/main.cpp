#include <iostream> 
#include "game.h"
#include "timer.h"
#include "menu.h"
#include "header.h"

using namespace std;


int main()
{
    // set the random seed
    srand(time(0));
    
    // uses windows.h to apply settings to console window for better gameplay
    try {
        configure_console();
    } 
    catch (exception error) {
        cout << error.what();
        return 0;
    }
    
    // game loop
    while (true) {
        // get instance of timer
        Timer* timer = Timer::getInstance();
        // create instance of game 
        Game game;
        // create header
        Header header(game.getLevel(), game.getlivesPtr());

        // pass reference to game to the timer so the update function can be called 
        (*timer).addGame(&game);

        bool run = true;

        while (run) {

            header.update();

            run = (*timer).run();

            // if P is pressed then pause and show menu
            if (GetKeyState('P') & 0x8000) {
                // debounce button with sleep
                Sleep(200);
                // dynamically create menu object and loop waiting for input
                Menu* menu = new Menu;
                int input = 0;
                while (!input) {
                    menu->drawMenu();
                    input = menu->listenInput();
                }
                delete menu;
                
                // decide what to do with input from menu
                // if not 1 or 2 then game will just continue
                switch (input) {
                case 1:
                    // restart
                    run = false;
                    break;
                case 2:
                    // quit
                    return 0;
                    break;
                }
            }
        }
        // remove this instance of game from timer when leaving loop 
        (*timer).removeGame();
    }
  
    return 0;
}

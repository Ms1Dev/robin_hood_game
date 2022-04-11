#include <iostream> 
#include "game.h"
#include "timer.h"
#include "menu.h"
#include "header.h"


using namespace std;


int main()
{
    // set the random seed used in other files
    srand(time(0));
    
    // uses windows.h to apply settings to console window for better gameplay
    configure_console();
    
    // game loop
    while (true) {

        Header header;
        header.update();

        Timer* timer = Timer::getInstance();

        Game game;

        (*timer).addGame(&game);

        bool run = true;

        while (run) {

            run = (*timer).run();

            if (GetKeyState('P') & 0x8000) {
                Sleep(200);
                Menu* menu = new Menu;
                int input = 0;
                while (!input) {
                    menu->drawMenu();
                    input = menu->listenInput();
                }
                delete menu;

                switch (input) {
                case 1:
                    // restart
                    run = false;
                    break;
                case 2:
                    // quit
                    break;
                }
            }
        }
    }
  
    return 0;
}

#include <iostream> 
#include <time.h>
#include "display.h"
#include "unit.h"
#include "projectile.h"
#include "char2Ansi.h"

using namespace std;


int main()
{

    int background[yPixels][xPixels];
    
    std::ifstream file("background.txt");
    for (int i = 0; i < yPixels; i++) {
        for (int j = 0; j < xPixels; j++) {
            char pixel;
            file >> pixel;
            background[i][j] = cnvrt2ansi(pixel);
        }
    }
    file.close();



    ProjectileManager projectileManager;

    Unit unit(10, 44, 2, &projectileManager);

    unsigned long tickCount = 0;

    configure_console();

    while (true) {

        if (GetTickCount64() > tickCount) {
            // controls frame rate but is not ideal
            tickCount = GetTickCount64() + 60;

            // update projectiles
            projectileManager.update_projectiles(display);

            // update units
            unit.update(display);

            draw();
            reset_display(background);

            // get key input
            if ((GetKeyState(37) & 0x8000) && (unit.get_x() > 0)) {
                unit.move_h(true);
            }
            else if ((GetKeyState(39) & 0x8000)) {
                unit.move_h();
            }

            if (GetKeyState(32) & 0x8000) {
                unit.shoot();
            }
        }
    }
}

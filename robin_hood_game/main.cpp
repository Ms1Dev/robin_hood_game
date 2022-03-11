#include <iostream> 
#include <time.h>
#include "display.h"
#include "unit.h"
#include "projectile.h"
#include "char2Ansi.h"

using namespace std;


int main()
{

    ProjectileManager projectileManager;

    Unit unit(10, 60, 2, &projectileManager);

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
            reset_display();

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

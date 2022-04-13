#include "header.h"
#include <fstream>
#include "char2Ansi.h"
#include <Windows.h>



Header::Header(int level, int* lives)
    : levelWidget(),
    livesWidget()
{
    setBackground();
    livesPrev = 0;
    this->lives = lives;
    this->level = level;
}


void Header::setBackground() {


    for (int i = 0; i < headerHeight; i++) {
        for (int j = 0; j < xPixels; j++) {
            char pixel = 'y';
            if (i == 0 || i == 1 || i == 18 || i == 19) {
                pixel = 'n';
            }
            headerDisplay[i][j] = cnvrt2ansi(pixel);
        }
    }
    
}


void Header::update() {

    if (livesPrev != *lives) {
        livesPrev = *lives;
        levelWidget.update(level);
        livesWidget.update(*lives);
        global_updateHeaderFlag = true;
    }
}
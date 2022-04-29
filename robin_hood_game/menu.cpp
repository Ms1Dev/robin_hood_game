#include "menu.h"
#include <fstream>
#include "char2Ansi.h"



Menu::Menu() {
    state = 0;
    width = 47;
    height = 30;
    x = xPixels / 2 - width / 2;
    y = yPixels / 2 - height / 2;
}


void Menu::drawMenu() {
    int memSize = height * width;

    // allocate memory to put background image
    int* imgData = new int[memSize] {};

    string filepath = "images/menu/";

    // set the image file to use depending on the state the menu is in
    switch (state) {
    case 0:
        filepath += "options.txt";
        break;
    case 1:
        filepath += "sureRestart.txt";
        break;
    case 2:
        filepath += "sureQuit.txt";
        break;
    }

    // load the image from file
    std::ifstream file(filepath);

    char pixel;
    int counter = 0;
    while (file.get(pixel) && counter < memSize) {
        if (pixel == '\n' || pixel == ' ') {
            continue;
        }

        imgData[counter] = cnvrt2ansi(pixel);
        counter++;
    }
    file.close();


    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            display[i + y][j + x] = imgData[j + width * i];
        }
    }
    delete[] imgData;

    // call the display draw function
    draw();
}

// listen for key inputs
int Menu::listenInput() {
    // select quit game
    if (GetKeyState('Q') & 0x8000) {
        state = 2;
    }
    // select reset game
    else if (GetKeyState('R') & 0x8000) {
        state = 1;
    }
    // if 'p' is pressed again then return 9 which will resume game with no action
    if (GetKeyState('P') & 0x8000) {
        return 9;
    }

    // after quit or reset is selected then listen for 'n' and 'y' for are you sure message
    // 'y' will return the selected value 'n' will return 9 which is resume game no action
    if ((GetKeyState('Y') & 0x8000) && state != 0) {
        return state;
    }
    else if ((GetKeyState('N') & 0x8000) && state != 0) {
        return 9;
    }
    return 0;
}
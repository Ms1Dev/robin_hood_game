#pragma once

#include <fstream>
#include "char2Ansi.h"
#include "config.h"


class Background {
public:
	Background(){
    };

    void update(int (&display)[yPixels][xPixels]) {

        int memSize = yPixels * xPixels;

        // allocate memory to put background image
        int* bgData = new int[memSize]{};

        // load the image from file
        std::ifstream file("bg.txt");

        char pixel;
        int index = 0;
        while (file.get(pixel)) { 
            if (pixel == '\n' || pixel == ' ') {
                continue;
            }
            bgData[index] = cnvrt2ansi(pixel);
            index++;
        }
        file.close();

        for (int i = 0; i < yPixels; i++) {
            for (int j = 0; j < xPixels; j++) {
                display[i][j] = bgData[((j + scrollPos) % 100) + 100 * i];
            }
        }

        delete[] bgData;
    }

    void right_scroll(int distance) {
        scrollPos -= distance;
        if (scrollPos < 0) {
            scrollPos = 0;
        }
    }

    void left_scroll(int distance) {
        scrollPos += distance;
    }

private:
	int scrollPos = 0;

};

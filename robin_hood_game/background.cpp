#include "background.h"
#include "char2Ansi.h"


Background* Background::getInstance() {
    if (!instance) {
        instance = new Background;
    }
    return instance;
}

Background::~Background() {
}

void Background::update(int(&display)[yPixels][xPixels]) {

    int memSize = yPixels * xPixels;

    // allocate memory to put background image
    int* bgData = new int[memSize] {};

    // load the image from file
    std::ifstream file("images/bg.txt");

    int heightDiff = dimensions.height - yPixels;
    int ignorePixels = heightDiff * dimensions.width;
    char pixel;
    int index = 0;
    int counter = 0;
    while (file.get(pixel) && index < memSize) {
        if (pixel == '\n' || pixel == ' ') {
            continue;
        }

        if (counter >= ignorePixels) {
            bgData[index] = cnvrt2ansi(pixel);
            index++;
        }
        counter++;
    }
    file.close();


    for (int i = 0; i < yPixels; i++) {
        for (int j = 0; j < xPixels; j++) {
            display[i][j] = bgData[((j + scrollPos) % dimensions.width) + dimensions.width * i];
        }
    }

    delete[] bgData;
}

void Background::right_scroll(int distance) {
    scrollPos -= distance;
    if (scrollPos < 0) {
        scrollPos = 0;
    }
}

void Background::left_scroll(int distance) {
    scrollPos += distance;
}

int Background::get_unit_ypos(int heightFromBottom) {
    if (dimensions.height < yPixels) {
        return dimensions.height - heightFromBottom;
    }
    else {
        return yPixels - heightFromBottom;
    }
}

int Background::get_scroll_pos() {
    return scrollPos;
}


Background::Background() {
    set_dimensions();
};


void Background::set_dimensions() {
    // load the image from file
    std::ifstream file("images/bg.txt");

    int nlPos = 0;
    int noOfPixels = 0;
    char pixel;
    while (file.get(pixel)) {
        if (pixel == '\n' && nlPos == 0) {
            nlPos = noOfPixels;
        }
        if (pixel == '\n' || pixel == ' ') {
            continue;
        }
        noOfPixels++;
    }
    file.close();

    dimensions.width = nlPos;
    dimensions.height = noOfPixels / nlPos;
}

Background* Background::instance = (nullptr);

#include "background.h"
#include "char2Ansi.h"

Background* Background::instance = (nullptr);

Background* Background::getInstance() {
    if (!instance) {
        instance = new Background;
    }
    return instance;
}

Background::~Background() {}

void Background::update(int(&display)[yPixels][xPixels]) {

    int memSize = yPixels * xPixels;

    // allocate memory to put background image
    int* bgData = new int[memSize] {};

    // load the image from file
    std::ifstream file("images/bg.txt");

    // if height of console is changed in config then some pixels need to be ignored or image is distorted
    int heightDiff = dimensions.height - yPixels;
    int ignorePixels = heightDiff * dimensions.width;
    char pixel;
    int index = 0;
    int counter = 0;
    // read pixel data from file and ignore spaces and newlines
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

    // add image to display
    for (int i = 0; i < yPixels; i++) {
        for (int j = 0; j < xPixels; j++) {
            display[i][j] = bgData[((j + scrollPos) % dimensions.width) + dimensions.width * i];
        }
    }

    delete[] bgData;
}

// scroll the background to the right specified amount
void Background::right_scroll(int distance) {
    scrollPos -= distance;
    if (scrollPos < 0) {
        scrollPos = 0;
    }
}

// scroll the background to the left specified amount
void Background::left_scroll(int distance) {
    scrollPos += distance;
}

// this is used to make sure the units spawn at the same height even if the console is resized
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

void Background::reset_scroll_pos() {
    scrollPos = 0;
}

Background::Background() {
    set_dimensions();
};

// reads the background image file to get the dimensions of the background image
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

    // dimension width is the number of pixels to the first newline
    dimensions.width = nlPos;
    // dimension height is the total pixels divided by the width
    dimensions.height = noOfPixels / nlPos;
}


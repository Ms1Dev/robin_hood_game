#include "widget.h"
#include <fstream>
#include "char2Ansi.h"
#include "display.h"


#define ITEMHEIGHT 10
#define NUMWIDTH 8
#define HEARTWIDTH 9

int Widget::numbers[10][10][8] = {};


Widget::Widget() {
    setNumbers();
    itemPosy = 5;
}

// static function that creates an array of number images from file
void Widget::setNumbers() {
    // memory size for 10 numbers 
    int memSize = ITEMHEIGHT * NUMWIDTH * 10;

    // allocate memory to put number images
    int* imgData = new int[memSize] {};

    // load the file containing the images
    std::ifstream file("images/header/numbers.txt");

    char pixel;
    int counter = 0;
    // while loop used so spaces and newline can be ignored without incrementing counter
    while (file.get(pixel) && counter < memSize) {
        if (pixel == '\n' || pixel == ' ') {
            continue;
        }
        imgData[counter] = cnvrt2ansi(pixel);
        counter++;
    }
    file.close();

    // add image data to static array
    for (int n = 0; n < 10; n++) {
        for (int i = 0; i < ITEMHEIGHT; i++) {
            for (int j = 0; j < NUMWIDTH; j++) {
                Widget::numbers[n][i][j] = imgData[j + n * NUMWIDTH + i * 10 * NUMWIDTH];
            }
        }
    }

    delete[] imgData;
}


Level::Level() {
    height = headerHeight;
    width = 55;
    x = 0;
    y = 0;
    imageFile = "images/header/level.txt";
    itemPosx = 38;
}

// updates the items used in the level widget
void Level::update(int value) {
    // call widget update
    __super::update();

    // store two digits seperately
    int levelDigits[2] = { value / 10, value % 10 };

    for (int n = 0; n < 2; n++) {

        int xPos = itemPosx + NUMWIDTH * n;

        int memSize = ITEMHEIGHT * NUMWIDTH;

        int* imgData = new int[memSize];

        for (int i = 0; i < ITEMHEIGHT; i++) {
            for (int j = 0; j < NUMWIDTH; j++) {
                imgData[j + i * NUMWIDTH] = cnvrt2ansi(Widget::numbers[levelDigits[n]][i][j]);
            }
        }

        // create an image struct with relevant data
        Image numberImage = { ITEMHEIGHT,NUMWIDTH,xPos,itemPosy,imgData };
        // pass reference to image struct to display function
        addToDisplay(&numberImage);

        delete[] imgData;
    }
}


Lives::Lives() {
    height = headerHeight;
    width = 65;
    x = xPixels - width;
    y = 0;
    imageFile = "images/header/lives.txt";
    itemPosx = 36 + x;
}


// updates the heart items used in the widget object
void Lives::update(int value) {
    __super::update();

    for (int n = 0; n < value; n++) {

        int xPos = itemPosx + HEARTWIDTH * n;

        int memSize = ITEMHEIGHT * HEARTWIDTH;

        int* imgData = new int[memSize];

        std::ifstream file("images/header/heart.txt");
        for (int i = 0; i < memSize; i++) {
            char pixel;
            file >> pixel;
            imgData[i] = cnvrt2ansi(pixel);
        }
        file.close();

        Image heartImage = { ITEMHEIGHT,HEARTWIDTH,xPos,itemPosy,imgData };

        addToDisplay(&heartImage);

        delete[] imgData;
    }
}

// updates the widgets base image
void Widget::update() {

    int memSize = height * width;

    // allocate memory to put background image
    int* imgData = new int[memSize];

    // load the image from file
    std::ifstream file(imageFile);

    for (int i = 0; i < memSize; i++) {
        char pixel;
        file >> pixel;
        imgData[i] = cnvrt2ansi(pixel);
    }
    file.close();

    Image widgetImage = { height,width,x,y,imgData };

    addToDisplay(&widgetImage);

    delete[] imgData;

}


// adds image to display array
void Widget::addToDisplay(Image* image) {

    for (int i = 0; i < image->height; i++) {
        int dy = i + image->y;
        for (int j = 0; j < image->width; j++) {
            // 9 is transparent so don't add anything at this pixel
            if ((*image->imgData)[j + image->width * i] == 9) {
                continue;
            }
            int dx = j + image->x;
            if (dx < xPixels && dx > 0) {
                headerDisplay[dy][dx] = (*image->imgData)[j + image->width * i];
            }
        }
    }
}


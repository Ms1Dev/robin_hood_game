#include "header.h"
#include <fstream>
#include "char2Ansi.h"
#include <Windows.h>

#define NUMHEIGHT 10
#define NUMWIDTH 8


int Widget::numbers[10][10][8] = {};


Widget::Widget() {
    setNumbers();
}

Header::Header()
    : levelWidget(&level)
{
    level = 1;
    setBackground();
}


void Widget::setNumbers() {
    int memSize = NUMHEIGHT * 10 * NUMWIDTH;

    // allocate memory to put background image
    int* imgData = new int[memSize] {};

    // load the image from file
    std::ifstream file("images/header/numbers.txt");

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

    for (int n = 0; n < 10; n++) {
        for (int i = 0; i < NUMHEIGHT; i++) {
            for (int j = 0; j < NUMWIDTH; j++) {
                Widget::numbers[n][i][j] = imgData[j + n * NUMWIDTH + i * 10 * NUMWIDTH];
            }
        }
    }

    delete[] imgData;
}


void Header::setBackground() {


    for (int i = 0; i < headerHeight; i++) {
        for (int j = 0; j < xPixels; j++) {
            char pixel = 'N';
            if (i == 0 || i == 1 || i == 18 || i == 19) {
                pixel = 'n';
            }
            headerDisplay[i][j] = cnvrt2ansi(pixel);
        }
    }
    
}


void Header::update() {
    levelWidget.update();
    global_bodyOnlyFlag = false;
}


Level::Level(int* value) {
    height = headerHeight;
    width = 55;
    x = 0;
    y = 0;
    imageFile = "images/header/level.txt";
    numPosx = 38;
    numPosy = 5;
    this->value = value;
}


void Level::update() {
    __super::update();

    int levelDigits[2] = { *value / 10, *value % 10 };

    for (int n = 0; n < 2; n++) {

        int xPos = numPosx + NUMWIDTH * n;
        
        int memSize = NUMHEIGHT * NUMWIDTH;

        // allocate memory to put image
        int* imgData = new int[memSize];

        for (int i = 0; i < NUMHEIGHT; i++) {
            for (int j = 0; j < NUMWIDTH; j++) {
                imgData[j + i * NUMWIDTH] = cnvrt2ansi(Widget::numbers[levelDigits[n]][i][j]);
            }
        }

        Image numberImage = { NUMHEIGHT,NUMWIDTH,xPos,numPosy,imgData };
        
        addToDisplay(&numberImage);

        delete[] imgData;

    }
}


void Widget::addToDisplay(Image *image) {

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


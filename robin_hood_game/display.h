#include <iostream> 
#include <Windows.h>
#include <string>
#include "config.h"

#define HANDLE GetStdHandle(STD_OUTPUT_HANDLE)

using namespace std;

// boolean matrix representing all pixels on screen
int display[yPixels][xPixels];

string text = "\033[41m";

void draw() {
    // turns the display matrix into string and outputs to console

    // set cursor to topleft
    COORD cursor;
    cursor.X = 0;
    cursor.Y = 0;
    SetConsoleCursorPosition(HANDLE, cursor);

    // declare string var to hold output
    string output;

    for (int i = 0; i < yPixels; i += 2) {
        // each row of text is two rows of pixels
        int y1 = i;
        int y2 = i + 1;
        for (int j = 0; j < xPixels; j++) {
            // prints combination of block, half block and nbsp depending on which pixels are lit up
            int character = 223;
            int upperPixel = display[y1][j];
            int lowerPixel = display[y2][j];

            char buffer[sizeof(int)];

            _itoa_s(upperPixel + 30, buffer, 10);

            char buffer2[sizeof(int)];

            _itoa_s(lowerPixel + 40, buffer2, 10);

            output += "\033[";
            output += buffer;
            output += ";";
            output += buffer2;
            output += "m";
            output += character;
        }
        // add a line break after every row
        output += '\n';
    }
    output += text;
    // cout all rows
    cout << output;
}


void reset_display() {
    // reset the display array
    memset(display, 0, sizeof(display));
}

void configure_console() {
    // set the font size 
    CONSOLE_FONT_INFOEX font;
    font.cbSize = sizeof(font);
    font.nFont = 0;
    font.FontFamily = FF_SCRIPT;
    font.FontWeight = FW_NORMAL;
    font.dwFontSize.X = pixelSize[0];
    font.dwFontSize.Y = pixelSize[1];
    SetCurrentConsoleFontEx(HANDLE, FALSE, &font);





    COORD bufferDim = { xPixels + 1,(yPixels / 2) + 1 };

    SetConsoleScreenBufferSize(
        HANDLE,
        bufferDim
    );

    SMALL_RECT windowDim = { 0,0, xPixels,  (yPixels / 2) };

    SetConsoleWindowInfo(
        HANDLE,
        true,
        &windowDim
    );

    // maximize the console window
    HWND consoleWindow = GetConsoleWindow();
    //ShowWindow(consoleWindow, SW_MAXIMIZE);

    // set cursor to invisible
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.dwSize = 1;
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(HANDLE, &cursorInfo);

    DWORD mode;
    GetConsoleMode(HANDLE, &mode);
    DWORD newMode = mode;
    newMode &= ~ENABLE_WRAP_AT_EOL_OUTPUT;
    newMode &= ENABLE_VIRTUAL_TERMINAL_INPUT;
    SetConsoleMode(HANDLE, mode);

    /*DWORD prev_mode;
    GetConsoleMode(HANDLE, &prev_mode);
    SetConsoleMode(HANDLE, (&prev_mode, ENABLE_WRAP_AT_EOL_OUTPUT));*/
}


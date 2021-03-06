#include "display.h"

// global variable display represents all pixels in viewable area
int display[yPixels][xPixels];
int headerDisplay[headerHeight][xPixels];
bool global_updateHeaderFlag = false;

// used for dev to output string to console
string text = "\033[41m";


void draw() {
    // turns the display matrix into string and outputs to console

    // set cursor to topleft
    COORD cursor;
    cursor.X = 0;
    cursor.Y = (headerHeight / 2) * !global_updateHeaderFlag;
    SetConsoleCursorPosition(HANDLE, cursor);

    // declare string var to hold output
    string output;

    for (int i = 0; i < yPixels + (headerHeight * global_updateHeaderFlag); i += 2) {
        // each row of text is two rows of pixels
        int y1 = i;
        int y2 = i + 1;
        for (int j = 0; j < xPixels; j++) {

            int character = 223;

            int upperPixel;
            int lowerPixel;
            if (global_updateHeaderFlag && i < headerHeight) {
                upperPixel = headerDisplay[y1][j];
                lowerPixel = headerDisplay[y2][j];
            }
            else {
                upperPixel = display[y1 - global_updateHeaderFlag * headerHeight][j];
                lowerPixel = display[y2 - global_updateHeaderFlag * headerHeight][j];
            }

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

   if (global_updateHeaderFlag) {
        global_updateHeaderFlag = false;
   }
}


void configure_console() {

    // throw errors if config is not correct
    if ((yPixels % 2 != 0) | (headerHeight % 2 != 0)) {
        throw exception("Y Pixels or Header height cannot be an odd number");
    }
    if (yPixels < 40) {
        throw exception("Y pixels cannot be less than 40");
    }
    if ((xPixels < 150) | (xPixels > 250)) {
        throw exception("X pixels must be between 150 - 250");
    }

    // set the font size 
    CONSOLE_FONT_INFOEX font;
    font.cbSize = sizeof(font);
    font.nFont = 0;
    font.FontFamily = FF_SCRIPT;
    font.FontWeight = FW_NORMAL;
    font.dwFontSize.X = pixelSize[0];
    font.dwFontSize.Y = pixelSize[1];
    SetCurrentConsoleFontEx(HANDLE, FALSE, &font);

    // prevent console from being resized
    HWND consoleWindow = GetConsoleWindow();
    SetWindowLong(consoleWindow, GWL_STYLE, GetWindowLong(consoleWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);

    // prevent clicking console from stopping the program
    DWORD mode;
    GetConsoleMode(HANDLE, &mode);
    SetConsoleMode(HANDLE, mode & ~ENABLE_QUICK_EDIT_MODE);

    // set screen buffer size
    COORD bufferDim = { xPixels + 1, (yPixels / 2) + 1 + (headerHeight / 2)};
    SetConsoleScreenBufferSize(
        HANDLE,
        bufferDim
    );

    // set window size
    SMALL_RECT windowDim = { 0,0, xPixels, (yPixels / 2) + (headerHeight / 2)};
    SetConsoleWindowInfo(
        HANDLE,
        true,
        &windowDim
    );

    // set cursor to invisible
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.dwSize = 1;
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(HANDLE, &cursorInfo);
}


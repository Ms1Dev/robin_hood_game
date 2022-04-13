#include "char2Ansi.h"

// converts a char representing colour into the ansi escape integer used by the console 
int cnvrt2ansi(char charIn) {
    int charOut;
    switch (charIn) {
    // black
    case 'n':
        charOut = 0;
        break;
    // dark red
    case 'r':
        charOut = 1;
        break;
    // dark green
    case 'g':
        charOut = 2;
        break;
    // dark yellow
    case 'y':
        charOut = 3;
        break;
    // dark blue
    case 'b':
        charOut = 4;
        break;
    // dark pink
    case 'p':
        charOut = 5;
        break;
    // dark cyan
    case 'c':
        charOut = 6;
        break;
    // dark white (grey)
    case 'w':
        charOut = 7;
        break;
    // light black (grey)
    case 'N':
        charOut = 60;
        break;
    // light red
    case 'R':
        charOut = 61;
        break;
    // light green
    case 'G':
        charOut = 62;
        break;
    // light yellow
    case 'Y':
        charOut = 63;
        break;
    // light blue
    case 'B':
        charOut = 64;
        break;
    // light pink
    case 'P':
        charOut = 65;
        break;
    // light cyan
    case 'C':
        charOut = 66;
        break;
    // white
    case 'W':
        charOut = 67;
        break;
    // transparent
    case 't':
        charOut = 9;
        break;
    default:
        charOut = 9;
        break;
    }
    return charOut;
}

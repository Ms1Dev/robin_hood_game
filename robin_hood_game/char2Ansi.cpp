#include "char2Ansi.h"

int cnvrt2ansi(char charIn) {
    int charOut;
    switch (charIn) {
    case 'n':
        charOut = 0;
        break;
    case 'r':
        charOut = 1;
        break;
    case 'g':
        charOut = 2;
        break;
    case 'y':
        charOut = 3;
        break;
    case 'b':
        charOut = 4;
        break;
    case 'p':
        charOut = 5;
        break;
    case 'c':
        charOut = 6;
        break;
    case 'w':
        charOut = 7;
        break;
    case 'N':
        charOut = 60;
        break;
    case 'R':
        charOut = 61;
        break;
    case 'G':
        charOut = 62;
        break;
    case 'Y':
        charOut = 63;
        break;
    case 'B':
        charOut = 64;
        break;
    case 'P':
        charOut = 65;
        break;
    case 'C':
        charOut = 66;
        break;
    case 'W':
        charOut = 67;
        break;
    case 't':
        charOut = 9;
        break;
    default:
        charOut = 9;
        break;
    }
    return charOut;
}

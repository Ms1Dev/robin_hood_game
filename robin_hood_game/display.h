#include <iostream> 
#include <Windows.h>
#include <string>
#include "config.h"

#define HANDLE GetStdHandle(STD_OUTPUT_HANDLE)

using namespace std;

// this header file is included in 2 .cpp files so extern is used to prevent redefinition error
extern int display[yPixels][xPixels];

void draw();
void configure_console();


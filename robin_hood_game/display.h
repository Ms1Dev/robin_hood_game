#pragma once

#include <iostream> 
#include <Windows.h>
#include <string>
#include "config.h"

#define HANDLE GetStdHandle(STD_OUTPUT_HANDLE)

using namespace std;

// global variables used for rendering the display
extern int display[yPixels][xPixels];
extern int headerDisplay[headerHeight][xPixels];
extern bool global_updateHeaderFlag;

void draw();
void configure_console();


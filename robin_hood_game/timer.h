#pragma once


#include <iostream>
#include <chrono>


class Game;

class Timer {

private:
    Timer();
    std::chrono::system_clock::time_point startTime;
    std::chrono::duration<float> deltaTime;
    unsigned long ticks;
    float fps;
    void reset();
    float delta_time();
    static Timer* instance;
    Game* game;
    
public:
    ~Timer();
    static Timer* getInstance();
    bool run();
    unsigned long get_ticks();
    void set_fps(float fps);
    void addGame(Game* game);
    void removeGame();
};


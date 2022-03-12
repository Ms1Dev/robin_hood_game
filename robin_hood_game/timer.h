#pragma once


#include <iostream>
#include <chrono>


class Timer {

private:
    Timer();
    std::chrono::system_clock::time_point startTime;
    std::chrono::duration<float> deltaTime;
    unsigned long ticks;
    float fps;
    void reset();
    float delta_time();
    void (*onTickFunc)();
    static Timer* instance;

public:
    static Timer *getInstance();
    void run();
    unsigned long get_ticks();
    void on_tick(void (*method)());
    void set_fps(float fps);
};


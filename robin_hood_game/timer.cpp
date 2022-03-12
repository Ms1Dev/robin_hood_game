#include "timer.h"


Timer* Timer::instance(nullptr);

Timer::Timer() {
    reset();
    deltaTime = std::chrono::duration<float>(0.0);
    ticks = 0;
    fps = 24;
}

Timer *Timer::getInstance() {
    if (!instance) {
        instance = new Timer;
    }
    return instance;
}

void Timer::run() {
    deltaTime = std::chrono::system_clock::now() - startTime;
    if (delta_time() >= 1 / fps) {
        reset();
        ticks++;
        onTickFunc();
    }
}
unsigned long Timer::get_ticks() {
    return ticks;
}

void Timer::reset() {
    startTime = std::chrono::system_clock::now();
}
float Timer::delta_time() {
    return deltaTime.count();
}

void Timer::on_tick(void (*method)()) {
    onTickFunc = method;
}

void Timer::set_fps(float fps) {
    this->fps = fps;
}


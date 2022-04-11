#include "timer.h"
#include "game.h"

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

Timer::~Timer() {
    delete instance;
}

bool Timer::run() {
    deltaTime = std::chrono::system_clock::now() - startTime;
    bool run = true;
    if (delta_time() >= 1 / fps) {
        reset();
        ticks++;
        if (game) {
            run = game->update();
        }
    }
    return run;
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

void Timer::on_tick(bool (*method)()) {
    onTickFunc = method;
}

void Timer::set_fps(float fps) {
    this->fps = fps;
}

void Timer::addGame(Game* game) {
    this->game = game;
}


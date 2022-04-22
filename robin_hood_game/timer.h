#pragma once

#include <iostream>
#include <chrono>


/*
    Singleton class that controls timing of the application
    Increments a tick counter at regular intervals using delta time
    Takes a reference to a game object and calls the game's update function on every tick
*/

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


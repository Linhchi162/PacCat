#pragma once


#include <SDL.h>

class Timer {
public:
    Timer();

    bool isTimerStarted();

    bool isTimerPaused();

    void start();

    void stop();

    void pause();

    void resume();

    Uint32 getTicks();

private:
    Uint32 startTime;
    Uint32 pausedTime;
    bool isPaused;
};



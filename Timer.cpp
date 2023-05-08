#include"Timer.h"

Timer::Timer()
{
	startTime = 0;
    pausedTime = 0;
	isPaused = 0;
}

bool Timer:: isTimerStarted()
{
	return startTime > 0;
}

bool Timer::isTimerPaused() 
{
	return isPaused;
}

void Timer::start() {
    startTime = SDL_GetTicks();
    pausedTime = 0;
    isPaused = false;
}

void Timer::stop() {
    startTime = 0;
    pausedTime = 0;
    isPaused = false;
}

void Timer::pause() {
    if (isTimerStarted() && !isTimerPaused()) {
        pausedTime = SDL_GetTicks() - startTime;
        isPaused = true;
    }
}

void Timer::resume() {
    if (isTimerPaused()) {
        startTime = SDL_GetTicks() - pausedTime;
        pausedTime = 0;
        isPaused = false;
    }
}

Uint32 Timer::getTicks() {
    Uint32 time = 0;

    if (isTimerStarted()) {
        if (isTimerPaused()) {
            time = pausedTime;
        }
        else {
            time = SDL_GetTicks() - startTime;
        }
    }

    return time;
}

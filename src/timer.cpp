#include "../include/timer.h"
#include "SDL2/SDL.h"

Timer::Timer() {
    // Initialize variables
    startTicks = 0;
    pausedTicks = 0;

    paused = false;
    started = false;
}

void Timer::start() {
    // Start the timer
    started = true;

    // unpause the timer
    paused = false;

    // Get the current clock time
    startTicks = SDL_GetTicks();
    pausedTicks = 0;
}

void Timer::stop() {
    // Stop the timer
    started = false;

    // Unpause the timer
    paused = false;

    // Clear tick variables
    startTicks = 0;
    pausedTicks = 0;
}

void Timer::pause() {
    // If the Timer is running and isn't already paused
    if( started && !paused ) {
        // Pause the timer
        paused = true;

        // Calculate the paused ticks
        pausedTicks = SDL_GetTicks() - startTicks;
        startTicks = 0;
    }
}

void Timer::unpause() {
    //if the Timer is running and paused
    if( started && paused ) {
        //unpause the timer
        paused = false;

        //Reset the starting ticks
        startTicks = SDL_GetTicks() - pausedTicks;

        //Reset the pause ticks
        pausedTicks = 0;
    }
}

unsigned int Timer::getTicks(){
    // The time we will return
    unsigned int time = 0;

    // If the Timer is running
    if( started ) {
        // If the timer is paused
        if( paused ) {
            // Return the number of ticks when the timer was paused
            time = pausedTicks;
        }
        else {
            // Return the current time minus the start time
            time = SDL_GetTicks() - startTicks;
        }
    }

    return time;
}

bool Timer::isStarted() {
    // Timer is running and paused or unpaused;
    return started;
}

bool Timer::isPaused() {
    return paused;
}

void Timer::limitFps(int fps) {

}
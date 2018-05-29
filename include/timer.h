#pragma once

#include "SDL2/SDL.h"

extern int count;

class Timer {
    public:
        //Initializes variables
        Timer();

        //Clock actions
        void start();
        void stop();
        void pause();
        void unpause();

        //Gets the Timer's time
        unsigned int getTicks();

        //Checks status of Timer
        bool isStarted();
        bool isPaused();

        void waitFPS(int ticksPerFrame);

        // Calculated fps
        float fr;
    private:
        //The clock time when the Timer is started
        unsigned int startTicks;

        //The ticks stored when the timer was paused
        unsigned int pausedTicks;

        //The timer status
        bool paused;
        bool started;

        // FPS counter variables
        Uint32 frameStart = 0;
        int frameTime = 0;
};
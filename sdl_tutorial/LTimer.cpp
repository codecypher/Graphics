#include "LTimer.h"

// Initialize the variables
LTimer::LTimer() {
    mStartTicks = 0;
    mPausedTicks = 0;

    mPaused = false;
    mStarted = false;
}


// If we want to restart it we just call start again
void LTimer::start() {
    // Start the timer
    mStarted = true;

    // Unpause the timer
    mPaused = false;

    // Get the current clock time
    mStartTicks = SDL_GetTicks();
    mPausedTicks = 0;
}

// Reinitialize all the variables
void LTimer::stop() {
    // Stop the timer
    mStarted = false;

    // Unpause the timer
    mPaused = false;

    // Clear tick variables
    mStartTicks = 0;
    mPausedTicks = 0;
}


void LTimer::pause() {
    // If the timer is running and isn't already paused
    if (mStarted && !mPaused) {
        // Pause the timer
        mPaused = true;

        // Calculate the paused ticks.
        // Save the time when the timer was paused.
        mPausedTicks = SDL_GetTicks() - mStartTicks;
        mStartTicks = 0;
    }
}

void LTimer::unpause() {
    // If the timer is running and paused
    if (mStarted && mPaused) {
        // Unpause the timer
        mPaused = false;

        // Reset the starting ticks
        mStartTicks = SDL_GetTicks() - mPausedTicks;

        // Reset the paused ticks
        mPausedTicks = 0;
    }
}

// Getting the time is a little bit tricky since our timer can be running, paused, or stopped.
Uint32 LTimer::getTicks() {
    Uint32 time = 0;    // The actual timer time

    // If the timer is running
    if (mStarted) {
        // If the timer is paused
        if (mPaused) {
            // the time stored (number of ticks) when paused
            time = mPausedTicks;
        }
        else {
            // current time minus the start time
            time = SDL_GetTicks() - mStartTicks;
        }
    }

    return time;
}

// Timer is running and paused or unpaused
bool LTimer::isStarted() {
   
    return mStarted;
}

// Timer is running and paused
bool LTimer::isPaused() {
    return mPaused && mStarted;
}
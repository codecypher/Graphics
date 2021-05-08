#pragma once

#ifndef __LTIMER_H__
#define __LTIMER_H__

#include <SDL2/SDL.h>

// The application time based timer
class LTimer {
public:
    //Initializes variables
    LTimer();

    //The various clock actions
    void start();
    void stop();
    void pause();
    void unpause();

   
    Uint32 getTicks();      // Get the timer's time
    bool isStarted();       // Check status of the timer
    bool isPaused();

private:
    
    Uint32 mStartTicks;     // The clock time when the timer started    
    Uint32 mPausedTicks;    // The ticks stored when the timer was paused

    // The timer status
    bool mPaused;
    bool mStarted;
};

#endif
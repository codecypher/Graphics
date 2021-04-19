/*
 * mp3.h: Machine Problem 3
 * Read in the vector list file PIXA.DAT into an array, table, or list
 * and display it on the screen.
 */
#pragma once

// Demonstration of the #include guard idiom.
#ifndef __MP3_H_
#define __MP3_H_

// Global constants
const int WORLD_SIZE = 2000;
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const float SCALE_FACTOR = 0.003f;  // from experimentation
const int MAX = 100;

// Global Variables
std::vector<std::vector<int>> vPoints;        // vector list


//#include "resource.h"

#endif // !MP3_H_

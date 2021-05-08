// header.h : include file for standard system include files,
// or project specific include files
//

#pragma once

// Using the #include guard idiom.
#ifndef __MP4_H_
#define __MP4_H_

// Global constants
const int WORLD_SIZE = 2000;
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const float SCALE_FACTOR = 0.003f;  // from experimentation
const int MAX = 100;

// Global Variables
std::vector<std::vector<int>> vPoints;        // vector list

//#include "resource.h"

#endif
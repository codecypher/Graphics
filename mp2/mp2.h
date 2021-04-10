#pragma once

// Demonstration of the #include guard idiom.
// Note that the defined symbol can be arbitrary.
#ifndef MP2_H_
#define MP2_H_

// Global Variables
extern const int WORLD_SIZE;
extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
extern const float SCALE_FACTOR;
extern const int MAX;
extern vector<vector<int>> vPoints;        // vector list

//using namespace std;

//#include "resource.h"

#endif // !MP2_H_

/*
 * utils.h
 * Common functions that are useful across projects.
 */
#pragma once

// Demonstration of the #include guard idiom.
// Note that the defined symbol can be arbitrary.
#ifndef __UTILS_H_
#define __UTILS_H_

// Global constants
extern const int WORLD_SIZE;
extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
extern const float SCALE_FACTOR;
extern const int MAX;

// Global Variables
extern std::vector<std::vector<int>> vPoints;        // vector list


// Utility functions
std::string ltrim(std::string& str, std::string chars);
std::string rtrim(std::string& str, std::string chars);
std::string trim(std::string& str, std::string chars);

//vector<int> split(char* text, char* delimiter);
std::vector<int> split(const std::string& s, char delimiter = ' ');

std::string toString(std::vector<int> vec);

void print_debug(std::string buffer);
void test_trim();


#endif // UTILS_H_
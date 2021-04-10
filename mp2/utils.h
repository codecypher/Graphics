#pragma once

// Demonstration of the #include guard idiom.
// Note that the defined symbol can be arbitrary.
#ifndef UTILS_H_
#define UTILS_H_

#include <list>
#include <vector>
#include <algorithm>
#include <iterator>

string ltrim(string& str, string chars);
string rtrim(string& str, string chars);
string trim(string& str, string chars);

//vector<int> split(char* text, char* delimiter);
vector<int> split(const string& s, char delimiter = ' ');

string toString(vector<int> vec);

void print_debug(string buffer);
void test_trim();


#endif // UTILS_H_
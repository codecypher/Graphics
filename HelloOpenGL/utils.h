#pragma once

#include <string>

#include <vector>
//#include <algorithm>
//#include <iterator>

const int MAX_LEN = 100;

string reftTrim(string str, string chars);
string RightTrim(string str, string chars);
string trimString(string str, string chars);

vector<int> split(char* text, char* delimiter);
string toString(vector<int> vec);

void print_debug(string buffer);

#include "framework.h"
#include "utils.h"

string leftTrim(string str, string chars) {
    //str.erase(0, str.find_first_not_of(chars));
    return str;
}

string rightTrim(string str, string chars) {
    //str.erase(0, str.find_first_not_of(chars));
    return str;
}

string trimString(string str, string chars) {
    //str.erase(0, str.find_first_not_of(chars));
    return str;
}

vector<int> split(char* text, char* delim) {
    vector<int> stk;
    char* token = NULL;
    char* next_token = NULL;

    // Establish string and get the first token
    token = strtok_s(text, delim, &next_token);

    // While there are tokens in text
    while (token != NULL) {
        // Get next token:
        if (token != NULL) {
            int n = stoi(token);
            stk.push_back(n);
            token = strtok_s(NULL, delim, &next_token);
        }
    }

    return stk;
}

string toString(vector<int> vec) {
    ostringstream vts;

    if (!vec.empty())
    {
        // Convert all but the last element to avoid a trailing ","
        std::copy(vec.begin(), vec.end() - 1, std::ostream_iterator<int>(vts, ", "));

        // Now add the last element with no delimiter
        vts << vec.back();
    }
    return vts.str().c_str();
}

void print_debug(string buffer) {
    //char buffer[500];
    //snprintf(buffer, 100, "(%f, %f)\n", new_square[i][0], new_square[i][1]);
    //print_debug(buffer);
    OutputDebugStringA(buffer.c_str());
}


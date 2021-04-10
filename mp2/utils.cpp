#include "framework.h"
#include "utils.h"

string chars_to_trim = ".,/ ";

// Trim the given characters from start of string (in place)
// We arbitrarily specified characters "., ,, /" and whitespace to be trimmed.
string ltrim(string& str, string chars = chars_to_trim) {
    str.erase(0, str.find_first_not_of(chars));
    return str;
}

// Trim the given characters from end of string (in place)
string rtrim(string& str, string chars = chars_to_trim) {
    str.erase(0, str.find_first_not_of(chars));
    return str;
}

// // Trim the given characters from both ends of string (in place)
string trim(string& str, string chars = chars_to_trim) {
    str.erase(0, str.find_first_not_of(chars));
    return str;
}

// trim from start (copying)
static inline string ltrim_copy(string s, string chars = chars_to_trim) {
    ltrim(s);
    return s;
}

// trim from end (copying)
static inline string rtrim_copy(string s, string chars = chars_to_trim) {
    rtrim(s);
    return s;
}

// trim from both ends (copying)
static inline string trim_copy(string s, string chars = chars_to_trim) {
    trim(s);
    return s;
}


string toString(vector<int> vec) {
    ostringstream vts;

    if (!vec.empty()) {
        // Convert all but the last element to avoid a trailing ","
        std::copy(vec.begin(), vec.end() - 1, std::ostream_iterator<int>(vts, ", "));

        // Now add the last element with no delimiter
        vts << vec.back();
    }
    return vts.str().c_str();
}

// split a string
vector<int> split(const std::string& s, char delimiter) {
    vector<int> tokens;
    string token;
    istringstream tokenStream(s);
    int num;

    while (getline(tokenStream, token, delimiter)) {
        trim(token);
        // ignore blank space
        if (token.length() > 0 && token != "J") {
            stringstream(token) >> num;
            tokens.push_back(num);
        }
    }

    //for (int x : tokens)
    //    cout << x << " ";
    //cout << endl;

    return tokens;
}

//vector<int> split(char* text, char* delim) {
//    vector<int> stk;
//    char* token = NULL;
//    char* next_token = NULL;
//
//    // Establish string and get the first token
//    token = strtok_s(text, delim, &next_token);
//
//    // While there are tokens in text
//    while (token != NULL) {
//        // Get next token:
//        if (token != NULL) {
//            int n = stoi(token);
//            stk.push_back(n);
//            token = strtok_s(NULL, delim, &next_token);
//        }
//    }
//
//    return stk;
//}

void print_debug(string buffer) {
    //char buffer[500];
    //snprintf(buffer, 100, "(%f, %f)\n", new_square[i][0], new_square[i][1]);
    //print_debug(buffer);
    OutputDebugStringA(buffer.c_str());
}


void test_trim() {
    //string chars_to_trim = " ";
    string chars_to_trim = ".,/ ";
    string text = "  ,.,  C++ Standard";
    string text_copy = ltrim_copy(text, chars_to_trim);
    cout << text << endl;
    cout << text_copy << endl;
}

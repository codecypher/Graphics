#include "framework.h"
#include "utils.hpp"

std::string chars_to_trim = ".,/ ";

// Trim the given characters from start of string (in place)
// We arbitrarily specified characters "., ,, /" and whitespace to be trimmed.
std::string ltrim(std::string& str, std::string chars = chars_to_trim) {
    str.erase(0, str.find_first_not_of(chars));
    return str;
}

// Trim the given characters from end of string (in place)
std::string rtrim(std::string& str, std::string chars = chars_to_trim) {
    str.erase(0, str.find_first_not_of(chars));
    return str;
}

// // Trim the given characters from both ends of string (in place)
std::string trim(std::string& str, std::string chars = chars_to_trim) {
    str.erase(0, str.find_first_not_of(chars));
    return str;
}

// trim from start (copying)
static inline std::string ltrim_copy(std::string s, std::string chars = chars_to_trim) {
    ltrim(s);
    return s;
}

// trim from end (copying)
static inline std::string rtrim_copy(std::string s, std::string chars = chars_to_trim) {
    rtrim(s);
    return s;
}

// trim from both ends (copying)
static inline std::string trim_copy(std::string s, std::string chars = chars_to_trim) {
    trim(s);
    return s;
}


std::string toString(std::vector<int> vec) {
    std::ostringstream vts;

    if (!vec.empty()) {
        // Convert all but the last element to avoid a trailing ","
        std::copy(vec.begin(), vec.end() - 1, std::ostream_iterator<int>(vts, ", "));

        // Now add the last element with no delimiter
        vts << vec.back();
    }
    return vts.str().c_str();
}

// split a string
std::vector<float> split(const std::string& s, char delimiter) {
    float num;
    std::vector<float> tokens;
    std::string token;
    std::istringstream tokenStream(s);

    while (std::getline(tokenStream, token, delimiter)) {
        trim(token);
        // convert to uppercase
        transform(token.begin(), token.end(), token.begin(), std::toupper);
        // ignore blank space and J line
        if (token.length() > 0 && token != "J") {
            std::stringstream(token) >> num;
            tokens.push_back(num);
        }
    }

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

// copy vec4 to vector
void copy_to_vector(glm::vec3 x, std::vector<float> &v) {
    for (int i = 0; i < v.size(); i++) {
        v[i] = x[i];
    }
}



// display array
void print_array(float v[], std::string title) {
    int n = sizeof(v);
    int f = sizeof(float);
    //std::cout << "size: " << sizeof(v) << ", " << sizeof(float) << ", " << n/f << std::endl;
    std::cout << title << "(";
    for (int i = 0; i <= n/f; i++) {
        if (i == n / f)
            std::cout << v[i];
        else
            std::cout << v[i] << ", ";
    }
    std::cout << ")" << std::endl;
}

// display vector
void print_vector(std::vector<float> v) {
    std::cout << "(" << v[0] << ", " << v[1] << ", " << v[2] << ")" << std::endl;
}

// display 2d vector
void print_vector(std::vector<std::vector<float>> vPoints) {
    for (std::vector<float> v : vPoints) {
        std::cout << "(" << v[0] << ", " << v[1] << ", " << v[2] << ")" << std::endl;
    }
}

void test_trim() {
    //string chars_to_trim = " ";
    std::string chars_to_trim = ".,/ ";
    std::string text = "  ,.,  C++ Standard";
    std::string text_copy = ltrim_copy(text, chars_to_trim);
    std::cout << text << std::endl;
    std::cout << text_copy << std::endl;
}

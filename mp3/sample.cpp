/*
 * sample.cpp
 * Sample code used in experimentation
 */
#include "framework.h"
#include "utils.h"

int sample_read_file(std::string filename) {
    std::string line, sout;
    std::string chars_to_trim = ".,/ ";
    char seps[] = ",\n";

    // Read from the text file
    std::ifstream f_in(filename);
    if (f_in.fail()) {
        std::cerr << "File open error.\n";
        return 1;
    }

    // Read file line by line
    while (!f_in.eof()) {
        //trim(buffer, chars_to_trim);

        std::getline(f_in, line);  // read line

        std::vector<int> v = split(line);
        vPoints.push_back(v);

        // stringstream(line) >> price;
        //cout << "size: " << v.size() << endl;

        // display groups of points (separated by blank line)
        for (int x : v)
            std::cout << x << " ";
        std::cout << std::endl;

        // display groups without blank line
        if (v.size() > 0) {
            for (int x : v)
                std::cout << x << " ";
            std::cout << std::endl;
        }
    }

    f_in.close();   // Close the file

    // Display each group of points to console
    for (std::vector<int> v : vPoints) {
        if (v.size() == 0) {  // J line
            std::cout << "J" << std::endl;
        }
        else {
            for (int x : v) {
                std::cout << x << " ";
            }
            std::cout << std::endl;
        }
    }

    return 0;
}

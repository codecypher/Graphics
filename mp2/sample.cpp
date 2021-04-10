/*
 * sample.cpp
 * Sample code used in experimentation
 */
#include "framework.h"
#include "utils.h"
#include "mp2.h"

int sample_read_file(string filename) {
    string line, sout;
    string chars_to_trim = ".,/ ";
    char seps[] = ",\n";

    // Read from the text file
    ifstream f_in(filename);
    if (f_in.fail()) {
        cerr << "File open error.\n";
        return 1;
    }

    // Read file line by line
    while (!f_in.eof()) {
        //trim(buffer, chars_to_trim);

        getline(f_in, line);  // read line

        vector<int> v = split(line);
        vPoints.push_back(v);

        // stringstream(line) >> price;
        //cout << "size: " << v.size() << endl;

        // display groups of points (separated by blank line)
        for (int x : v)
            cout << x << " ";
        cout << endl;

        // display groups without blank line
        if (v.size() > 0) {
            for (int x : v)
                cout << x << " ";
            cout << endl;
        }
    }

    f_in.close();   // Close the file

    // Display each group of points to console
    for (vector<int> v : vPoints) {
        if (v.size() == 0) {  // J line
            cout << "J" << endl;
        }
        else {
            for (int x : v) {
                cout << x << " ";
            }
            cout << endl;
        }
    }

    return 0;
}

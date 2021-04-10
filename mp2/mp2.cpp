/*
 * mp2.cpp: Machine Problem 2
 * Read in the vector list file PIXA.DAT into an array, table, or list
 * and output the contents of the file to the console.
 */
#include "framework.h"
#include "utils.h"
#include "mp2.h"

// Global Variables
const int WORLD_SIZE = 2000;
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const float SCALE_FACTOR = 0.003f;  // from experimentation
const int MAX = 100;
vector<vector<int>> vPoints;        // vector list

// Called by OpenGL when it detects a keyboard event
void keyboard(unsigned char key, int x, int y) {
    // Called when a key is pressed 
    if (key == 27) exit(0);  // 27 is the Escape key
}

// Called by OpenGL when the window is created, moved, or resized 
void reshape(int width, int height) {
    glViewport(0, 0, (GLsizei)width, (GLsizei)height);
    glMatrixMode(GL_PROJECTION);                // select the projection matrix 
    glLoadIdentity();                           // start with a unit modelview matrix 
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);   // The unit cube 
    glMatrixMode(GL_MODELVIEW);                 // select the modelview matrix
    glLoadIdentity();                           // initialize it
    glScalef(SCALE_FACTOR, SCALE_FACTOR, 0.0);  // scale by (x, y, z)
}

// Called when OpenGL needs to update the display
void display() {
    // Translate coordinates from World to Screen
    float x_ratio = (float(SCREEN_WIDTH) - 1.0) / (2.0 * WORLD_SIZE);   // 639 / 2000 = 0.3195
    float y_ratio = (float(SCREEN_HEIGHT) - 1.0) / (2.0 * WORLD_SIZE);  // 479 / 2000 = 0.2395
    float z_ratio = 1.0;

    glColor3f(1.0f, 0.0f, 0.0f);    // red
    glClear(GL_COLOR_BUFFER_BIT);   // clear the window 

    gluLookAt(0.0, 0.0, 0.5,        // position of camera
        0.0, 0.0, 0.0,              // point at which camera looks
        0.0, 1.0, 0.0);             // "up" direction of camera 

    // Graph points
    float screen_x, screen_y, screen_z;
    glBegin(GL_LINE_STRIP);  // draw lines
    for (vector<int> v : vPoints) {
        if (v.size()) {  // ignore J line
            screen_x = v[0] * x_ratio;
            screen_y = v[1] * y_ratio;
            screen_z = v[2] * z_ratio;
            //cout << "(" << screen_x << ", " << screen_y << ") ";
            cout << "(" << v[0] << ", " << v[1] << ", " << v[2] << ") ";
            glVertex3f(screen_x, screen_y, screen_z);
        }
        cout << endl;
    }
    glEnd();
    glFlush();  // force update of screen
}

int main_opengl(int argc, char** argv) {
    glutInit(&argc, argv);              // initialise opengl 
    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);  // Set the window size 
    glutInitWindowPosition(100, 100);   // set the window position 
    glutCreateWindow("Square");         // create the window 
    glutDisplayFunc(display);           // register the display function 
    glutReshapeFunc(reshape);           // register the reshape function 
    glutKeyboardFunc(keyboard);         // register the keyboard function 
    glutMainLoop();                     // enter the opengl main loop 
    return 0;
}


int read_file(string filename) {
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
        getline(f_in, line);  // read line
        vector<int> v = split(line);
        vPoints.push_back(v);
    }

    f_in.close();   // Close the file

    return 0;
}


int main(int argc, char** argv) {
    ios::sync_with_stdio();  // notify compiler that both types of I/O will be used

    //string filename = "vector_list.dat";
    string filename = "pixa.dat";

    read_file(filename);
    main_opengl(argc, argv);

    system("pause");
}


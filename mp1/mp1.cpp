/*
 * mp1.cpp
 */
#include "mp1.h"

 // Global Variables
const int WORLD_SIZE = 1000;
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const float SCALE_FACTOR = 0.015f;  // from experimentation
const int MAX = 100;

float world[][2] = { {-100.0, -100.0}, {100.0, -100.0}, {100.0, 100.0}, {-100.0, 100.0} };
float screen[][2] = { {0.0, 0.0}, {0.0, 0.0}, {0.0, 0.0}, {0.0, 0.0} };

void print_debug(string buffer) {
    //char buffer[500];
    //snprintf(buffer, 100, "(%f, %f)\n", new_square[i][0], new_square[i][1]);
    //print_debug(buffer);
    OutputDebugStringA(buffer.c_str());
}

void keyboard(unsigned char key, int x, int y) {
    // Called when a key is pressed 
    if (key == 27) exit(0);  // 27 is the Escape key
}

// Called when the window is created, moved, or resized 
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
void display(void) {
    // Translate coordinates from World to Screen
    float x_ratio = (float(SCREEN_WIDTH) - 1.0) / (2.0 * WORLD_SIZE);   // 639 / 2000 = 0.3195
    float y_ratio = (float(SCREEN_HEIGHT) - 1.0) / (2.0 * WORLD_SIZE);  // 479 / 2000 = 0.2395
    for (int i = 0; i < 4; i++) {
        screen[i][0] = world[i][0] * x_ratio;
        screen[i][1] = world[i][1] * y_ratio;
    }

    glColor3f(1.0f, 0.0f, 0.0f);    // red
    glClear(GL_COLOR_BUFFER_BIT);   // clear the window 

    gluLookAt(0.0, 0.0, 0.5,        // position of camera
              0.0, 0.0, 0.0,        // point at which camera looks
              0.0, 1.0, 0.0);       // "up" direction of camera 

    glBegin(GL_LINE_LOOP);  // draw a square 
        glVertex2f(screen[0][0], screen[0][1]);
        glVertex2f(screen[1][0], screen[1][1]);
        glVertex2f(screen[2][0], screen[2][1]);
        glVertex2f(screen[3][0], screen[3][1]);
    glEnd();
    glFlush();  // force update of screen
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);          // initialise opengl 
    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);  // Set the window size 
    glutInitWindowPosition(100, 100);   // set the window position 
    glutCreateWindow("Square");     // create the window 
    glutDisplayFunc(display);       // register the display function 
    glutReshapeFunc(reshape);       // register the reshape function 
    glutKeyboardFunc(keyboard);     // register the keyboard function 
    glutMainLoop();                 // enter the opengl main loop 
    return 0;
}


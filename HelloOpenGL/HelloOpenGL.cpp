/*
 * HelloOpenGL.cpp: Test OpenGL C/C++ Setup
 */
#include "framework.h"
#include "utils.h"
#include "HelloOpenGL.h"

 // Global Variables
const int WORLD_SIZE = 1000;
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const float SCALE_FACTOR = 0.015f;
const int MAX = 100;

float world[][2] = { {-100.0, -100.0}, {100.0, -100.0}, {100.0, 100.0}, {-100.0, 100.0} };
float screen[][2] = { {0.0, 0.0}, {0.0, 0.0}, {0.0, 0.0}, {0.0, 0.0} };

// Handler for window repaint event. 
// Call back when the window first appears or needs to be repainted.
void display_red_square() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
    glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer

    // Draw a Red 1x1 Square centered at origin
    glBegin(GL_QUADS);                  // Each set of 4 vertices form a quad
        glColor3f(1.0f, 0.0f, 0.0f);    // Red
        glVertex2f(-0.5f, -0.5f);       // x, y
        glVertex2f(0.5f, -0.5f);
        glVertex2f(0.5f, 0.5f);
        glVertex2f(-0.5f, 0.5f);
    glEnd();

    glFlush();  // Render now
}

int main_red_square(int argc, char** argv) {
    glutInit(&argc, argv);                  // Initialize GLUT
    glutCreateWindow("OpenGL Setup Test");  // Create a window with the given title
    glutInitWindowSize(320, 320);           // Set the window's initial width & height
    glutInitWindowPosition(50, 50);         // Position the window's initial top-left corner
    glutDisplayFunc(display_red_square);    // Register display callback handler for window re-paint
    glutMainLoop();                         // Enter the infinitely event-processing loop
    return 0;
}


// Called when OpenGL needs to update the display
void display_ex3(void) {
    glClearColor(1.0, 1.0, 1.0, 0.0);   
    glClear(GL_COLOR_BUFFER_BIT);       // Clear the window
    glFlush();                          // Force update of screen
}

void keyboard(unsigned char key, int x, int y) {
    // Called when a key is pressed 
    if (key == 27) exit(0);  // 27 is the Escape key
}


int main_ex3(int argc, char** argv) {
    glutInit(&argc, argv);              // initialize OpenGL 
    glutInitWindowSize(500, 500);       // set the window size
    glutInitWindowPosition(100, 100);   // set the window position 
    glutCreateWindow("ex3");            // create the window 
    glutDisplayFunc(display_ex3);       // register the "display" function 
    glutKeyboardFunc(keyboard);         // register the "keyboard" function
    glutMainLoop();                     // enter the OpenGL main loop
    return 0;
}



// Called when OpenGL needs to update the display
void display_ex4(void) {
    glClear(GL_COLOR_BUFFER_BIT);  // clear the window 
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 0.5, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glBegin(GL_LINE_LOOP);  // draw a triangle 
        glVertex3f(-0.3, -0.3, 0.0);
        glVertex3f(0.0, 0.3, 0.0);
        glVertex3f(0.3, -0.3, 0.0);
    glEnd();
    glFlush();  // force update of screen
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

int main_square(int argc, char** argv) {
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


int read_file() {
    string sOutput = "";
    char chars_to_trim[] = ".,/ ";
    char seps[] = ",\n";

    // Read from the text file
    ifstream f_in("vector_list.txt");
    if (f_in.fail()) {
        cerr << "File open error.\n";
        return 1;
    }

    // Read vector file file line by line
    char buffer[MAX];                   // string to output the text file
    f_in.getline(buffer, MAX, '\n');    // prime the pump
    while (!f_in.eof()) {
        // Output the text from the file
        trimString(buffer, chars_to_trim);

        //print_debug(buffer);

        vector<int> vList = split(buffer, seps);
        sOutput = toString(vList) + "\n";
        print_debug(sOutput);

        // Translate coordinate from World to Screen
        //double x_screen = (vList[0] + WORLD_SIZE) * x_ratio;
        //double y_screen = (vList[1] + WORLD_SIZE) * y_ratio;
        //sOutput = to_string(x_screen) + " " + to_string(y_screen) + "\n";
        //OutputDebugStringA(sOutput.c_str());

        // Draw point on screen

        f_in.getline(buffer, MAX, '\n');    // read next line
    }

    // Close the file
    f_in.close();

    return 0;
}

int main(int argc, char** argv) {
    ios::sync_with_stdio();  // notify compiler that both types of I/O will be used

    //main_red_square(argc, argv);
    //main_ex4(argc, argv);
    main_square(argc, argv);

    //read_file();
}


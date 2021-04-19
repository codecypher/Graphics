// HelloSFML.cpp : This file contains the 'main' function. 
//

#include "HelloSFML.h"

// Global Variables
const int WORLD_SIZE = 1000;
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const float SCALE_FACTOR = 0.015f;
const int MAX = 100;

float world[][2] = { {-100.0, -100.0}, {100.0, -100.0}, {100.0, 100.0}, {-100.0, 100.0} };
float screen[][2] = { {0.0, 0.0}, {0.0, 0.0}, {0.0, 0.0}, {0.0, 0.0} };


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


// Note that we are using the sf namespace.
int main_sfml() {
    sf::RenderWindow window(sf::VideoMode(640, 480), "SFML works!");
    sf::CircleShape shape(200.f);
    shape.setFillColor(sf::Color::Green);

    // start the game loop (as long as the window is open)
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();      // clear the screen
        window.draw(shape);  // draw the shape
        window.display();    // update the window
    }

    return 0;
}


int main(int argc, char** argv) {
    ios::sync_with_stdio();  // notify compiler that both types of I/O will be used
    main_square(argc, argv);
    //main_sfml();
}


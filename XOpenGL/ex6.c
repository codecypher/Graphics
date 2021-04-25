/*
 * ex6.c
 * Example 6: A rotating cube
 */
#include "ex6.h"

GLfloat angle= 0.0;

void spin (void) {
    angle += 1.0;
    glutPostRedisplay();
}

// Called when OpenGL needs to update the display
void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);   // Clear the window
    glLoadIdentity ();
    gluLookAt (0.0, 0.0, 0.5, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glRotatef(angle, 1, 0, 0);
    glRotatef(angle, 0, 1, 0);
    glRotatef(angle, 0, 0, 1);
    glutWireCube(2.0);
    glFlush();                     // Force update of screen
}

// Called when a key is pressed*
void keyboard(unsigned char key, int x, int y) {
    if (key == 27) exit (0);    // 27 is the Escape key
}

// Called when the window is created, moved or resized
void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);  // Select the projection matrix
    glLoadIdentity();             // Initialise it
    gluPerspective (60, (GLfloat)w / (GLfloat)h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);   // Select the modelview matrix
}

int main_ex6(int argc, char** argv) {
    glutInit(&argc, argv);              // Initialise OpenGL
    glutInitWindowSize (500, 500);      // Set the window size
    glutInitWindowPosition (100, 100);  // Set the window position
    glutCreateWindow("ex6: A rotating cube");            // Create the window
    glutDisplayFunc(display);           // Register the "display" function
    glutReshapeFunc(reshape);           // Register the "reshape" function
    glutKeyboardFunc(keyboard);         // Register the "keyboard" function
    glutIdleFunc(spin);                 // Register the "idle" function
    glutMainLoop();                     // Enter the OpenGL main loop
    return 0;
}

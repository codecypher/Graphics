#include "ex8.hpp"

float r = 0.0;
int hidden= 0;

void Ex8::init(void) {
    glClearColor (0.0, 0.0, 0.0, 0.0);
}

void Ex8::spin (void) {
    r += 1.0;
    glutPostRedisplay();
}

// Called when OpenGL needs to update the display
void Ex8::display(void) {
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   // Clear the window
    
    if (hidden)
        glEnable(GL_DEPTH_TEST);
    else
        glDisable(GL_DEPTH_TEST);
    
    glLoadIdentity ();
    gluLookAt (0.0, 0.0, 0.5,
               0.0, 0.0, 0.0,
               0.0, 1.0, 0.0);
    
    glColor3f (1.0, 0.0, 0.0);
    glutSolidCube(1.0);             // red cube

    glRotatef(r*2.0, 1, 0, 0);      // orbit angle
    glTranslatef(0.0, 0.0, 1.0);    // orbit radius
    
    glRotatef(r, 1, 0, 0);          // tumble in x, y, z
    glRotatef(r, 0, 1, 0);
    glRotatef(r, 0, 1, 1);
    
    glColor3f (0.0, 1.0, 0.0);
    
    glutSolidCube(0.5);             // green cube

    glutSwapBuffers();  // Double-buffering
}

// Called when a key is pressed*
void Ex8::keyboard(unsigned char key, int x, int y) {
    if (key == 27) exit (0);    // escape key
    if (key == 'h')
        hidden = !hidden;
}

// Called when the window is created, moved or resized
void Ex8::reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);  // Select the projection matrix
    glLoadIdentity();             // Initialise it
    gluPerspective (60, (GLfloat)w / (GLfloat)h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);   // Select the modelview matrix
}

int Ex8::main(int argc, char** argv) {
    glutInit(&argc, argv);              // Initialise OpenGL
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize (500, 500);      // Set the window size
    glutInitWindowPosition (100, 100);  // Set the window position
    glutInitDisplayMode (GLUT_DOUBLE);
    glutCreateWindow("ex8");            // Create the window
    init();
    glutDisplayFunc(Ex8::display);      // Register the "display" function
    glutReshapeFunc(Ex8::reshape);      // Register the "reshape" function
    glutKeyboardFunc(Ex8::keyboard);    // Register the "keyboard" function
    glutIdleFunc(Ex8::spin);            // Register the "idle" function
    glutMainLoop();                     // Enter the OpenGL main loop
    return 0;
}

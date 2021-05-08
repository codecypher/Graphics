#include "framework.h"
#include "Simple.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "glm/ext.hpp"

#include "include/linmath.h"

#include <math.h>


Simple::Simple() {
}

// initialize constants
const int  Simple::SCREEN_WIDTH = 640;
const int  Simple::SCREEN_HEIGHT = 480;
const int  Simple::WORLD_SIZE = 2000;
const float Simple::rotations_per_tick = 0.2;

// initialize static member variables
float Simple::rotate_y = 0;
float Simple::rotate_z = 0;
float Simple::prev_time = 0;

void Simple::Init() {
}

// Called by OpenGL when it detects a keyboard event (key is pressed)
void Simple::process_input_simple(GLFWwindow* window, int key, int scancode, int action, int mods) {
    unsigned char prev = 'Z';

    // calculate elapsed time and the amount by which stuff rotates
    double current_time = glfwGetTime();
    double delta_rotate = (current_time - prev_time) * rotations_per_tick * 360;

    //prev_time = current_time;

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        rotate_y += delta_rotate;

    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        rotate_y -= delta_rotate;

    // z axis always rotates
    rotate_z += delta_rotate;

    prev = key;

    //glfwPostRedisplay();
}

void Simple::DrawSquare() {
    //glMatrixMode(GL_MODELVIEW);
    //glLoadIdentity();              // start with a unit modelview matrix

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
    glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer

    glColor3f(1.0f, 0.0f, 0.0f);   // Red

    glMatrixMode(GL_MODELVIEW);
    glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 5.0f, -10.0f),     // position of camera
        glm::vec3(0.0f, 0.0f, 0.0f),     // point at which camera looks (target)
        glm::vec3(0.0f, 1.0f, 0.0f));    // up direction of camera
    glPushMatrix();
    glMultMatrixf(glm::value_ptr(view));
    glPopMatrix();

    // Draw a square centered at origin
    glBegin(GL_QUADS);                  // Each set of 4 vertices form a quad
        glVertex2f(-0.5f, -0.5f); 
        glVertex2f(0.5f, -0.5f);
        glVertex2f(0.5f, 0.5f);
        glVertex2f(-0.5f, 0.5f);
    glEnd();

    glFlush();  // Render now
}

void Simple::DrawTriangle() {
    glMatrixMode(GL_MODELVIEW);

    glm::mat4 view;
    view = glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f),     // camera position
        glm::vec3(0.0f, 0.0f, -1.0f),                   // point at which camera looks (target)
        glm::vec3(0.0f, 1.0f, 0.0f));                   // up direction

    //glMultMatrixf(glm::value_ptr(view));

    glPushMatrix();
    glMultMatrixf(glm::value_ptr(view));
    glPopMatrix();

    glColor3f(1.0f, 0.0f, 0.0f);    // Red

    // draw a triangle
    glBegin(GL_LINE_LOOP); 
        //glVertex3f(-0.3, -0.3, 0.0);
        //glVertex3f(0.0, 0.3, 0.0);
        //glVertex3f(0.3, -0.3, 0.0);
        glVertex3f(-0.5, -0.5, 0.0);
        glVertex3f(0.0, 0.5, 0.0);
        glVertex3f(0.5, -0.5, 0.0);
        glEnd();
}

int Simple::main_gl(int argc, char** argv) {
    if (glfwInit() != GL_TRUE) {
        glfwTerminate();
        exit(-1);
    }

    GLFWwindow* window = glfwCreateWindow(640, 480, "Simple", NULL, NULL);
    if (!window) {
        glfwTerminate();
        exit(-1);
    }
    glfwMakeContextCurrent(window);

    glfwSetKeyCallback(window, process_input_simple);
    gladLoadGL();
    glfwSwapInterval(1);

    //glfwSetFramebufferSizeCallback(window, resize_simple);  // register the callback function

    // initialize Glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        exit(EXIT_FAILURE);
    }

    Init();

    prev_time = glfwGetTime();  // the time of the previous frame

    // event loop
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // clear the buffer        

        DrawSquare();                // draw the figure 
        //DrawTriangle();

        glfwSwapBuffers(window);    // swap the buffers
        glfwPollEvents();           // poll IO events
    }

    glfwTerminate();

    return 0;
}

#include "framework.h"
#include "RotateSquares.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "glm/ext.hpp"

#include "include/linmath.h"

#include <math.h>


RotateSquares::RotateSquares() {
}

// initialize constants
const int  RotateSquares::SCREEN_WIDTH = 640;
const int  RotateSquares::SCREEN_HEIGHT = 480;
const int  RotateSquares::WORLD_SIZE = 2000;
const float RotateSquares::rotations_per_tick = 0.2;

// initialize static member variables
float RotateSquares::rotate_y = 0;
float RotateSquares::rotate_z = 0;
float RotateSquares::prev_time = 0;

void RotateSquares::Init() {
    // set the projection matrix to a normal frustum with a max depth of 50
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float aspect_ratio = ((float)SCREEN_HEIGHT) / SCREEN_WIDTH;
    glFrustum(.5, -.5, -.5 * aspect_ratio, .5 * aspect_ratio, 1, 50);
    glMatrixMode(GL_MODELVIEW);
}

// Called by OpenGL when it detects a keyboard event (key is pressed)
void RotateSquares::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
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
}


// Draw a RotateSquares with a gradient color at coordinates 0, 10
void RotateSquares::Draw_Squares(float red, float green, float blue) {
    glBegin(GL_QUADS); {
        glColor3f(red, green, blue);
        glVertex2i(1, 11);
        glColor3f(red * .8, green * .8, blue * .8);
        glVertex2i(-1, 11);
        glColor3f(red * .5, green * .5, blue * .5);
        glVertex2i(-1, 9);
        glColor3f(red * .8, green * .8, blue * .8);
        glVertex2i(1, 9);
    }
    glEnd();
}

void RotateSquares::Draw() {
    // reset view matrix
    glLoadIdentity();
    
    // move view back a bit
    glTranslatef(0, 0, -30);

    // apply the current rotation
    glRotatef(rotate_y, 0, 1, 0);
    glRotatef(rotate_z, 0, 0, 1);

    // by repeatedly rotating the view matrix during drawing, the
    // RotateSquaress end up in a circle
    int i = 0, RotateSquaress = 15;
    float red = 0, blue = 1;
    for (; i < RotateSquaress; ++i) {
        glRotatef(360.0 / RotateSquaress, 0, 0, 1);
        // colors change for each RotateSquares
        red += 1.0 / 12;
        blue -= 1.0 / 12;
        Draw_Squares(red, .6, blue);
    }
}

int RotateSquares::main_gl(int argc, char** argv) {
    if (glfwInit() != GL_TRUE) {
        glfwTerminate();
        exit(-1);
    }

    GLFWwindow* window = glfwCreateWindow(640, 480, "RotateSquares", NULL, NULL);
    if (!window) {
        glfwTerminate();
        exit(-1);
    }
    glfwMakeContextCurrent(window);

    glfwSetKeyCallback(window, key_callback);
    gladLoadGL();
    glfwSwapInterval(1);

    //glfwSetFramebufferSizeCallback(window, resize_callback);  // register the resize function

    // initialize Glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        exit(EXIT_FAILURE);
    }

    Init();
    
    prev_time = glfwGetTime();  // the time of the previous frame

    // event loop
    while (!glfwWindowShouldClose(window)) {
        // calculate elapsed time and the amount by which stuff rotates
        double current_time = glfwGetTime();
        double delta_rotate = (current_time - prev_time) * rotations_per_tick * 360;

        prev_time = current_time;
        
        rotate_z += delta_rotate;   // z axis always rotates

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // clear the buffer        

        Draw();                     // draw the figure 

        glfwSwapBuffers(window);    // swap the buffers
        glfwPollEvents();           // poll IO events
    }

    glfwTerminate();

    return 0;
}

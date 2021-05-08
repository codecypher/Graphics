#include "framework.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "glm/ext.hpp"

#include <math.h>

#include "include/linmath.h"

#include "Triangle.h"

Triangle::Triangle() {
}

static const struct {
    float x, y;
    float r, g, b;
} vertices[3] =
{
    { -0.6f, -0.4f, 1.0f, 0.0f, 0.0f },
    {  0.6f, -0.4f, 0.0f, 1.0f, 0.0f },
    {  0.0f,  0.6f, 0.0f, 0.0f, 1.0f }
};

static const char* vertex_shader_text =
"#version 110\n"
"uniform mat4 MVP;\n"
"attribute vec3 vCol;\n"
"attribute vec2 vPos;\n"
"varying vec3 color;\n"
"void main()\n"
"{\n"
"    gl_Position = MVP * vec4(vPos, 0.0, 1.0);\n"
"    color = vCol;\n"
"}\n";

static const char* fragment_shader_text =
"#version 110\n"
"varying vec3 color;\n"
"void main()\n"
"{\n"
"    gl_FragColor = vec4(color, 1.0);\n"
"}\n";


void Triangle::error_callback(int error, const char* description) {
    //fprintf(stderr, "Error: %s\n", description);
    std::cout << "Error: " << description << std::endl;
}


// Called by OpenGL when it detects a keyboard event (key is pressed)
void Triangle::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    unsigned char prev = 'Z';

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    prev = key;
}


// This function creates a 640 by 480 window and starts a loop
// that clears the screen, renders a triangle, and processes IO events
// until the user presses Escape or closes the window.
int Triangle::main_gl(int argc, char** argv) {
    // notify compiler that both types of I/O will be used
    std::ios::sync_with_stdio();

    GLFWwindow* window;
    GLuint vertex_buffer, vertex_shader, fragment_shader, program;
    GLint mvp_location, vpos_location, vcol_location;

    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    window = glfwCreateWindow(640, 480, "Triangle example", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwSetKeyCallback(window, key_callback);

    glfwMakeContextCurrent(window);
    gladLoadGL();

    // The swap interval indicates how many frames to wait
    // until swapping the buffers which is commonly known as vsync.
    //
    // If the buffers are swapped in the middle of the screen update,
    // this can lead to screen tearing.
    glfwSwapInterval(1);

    // Create vertex buffer object (VBO)
    glGenBuffers(1, &vertex_buffer);
    // Copy our vertex array into a buffer for OpenGL to use
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Create vertex shader
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_text, NULL);
    glCompileShader(vertex_shader);

    // Create fragment shader
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_text, NULL);
    glCompileShader(fragment_shader);

    // Link the shader objects into a shader program that we can use for rendering
    program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);

    mvp_location = glGetUniformLocation(program, "MVP");
    vpos_location = glGetAttribLocation(program, "vPos");
    vcol_location = glGetAttribLocation(program, "vCol");

    // Linking Vertex Attributes
    // Tell OpenGL how to interpret the vertex data (per vertex attribute)

    // Set the vertex attributes pointers
    // The fifth parameter is known as the stride which is the space between consecutive vertex attributes.
    // The last parameter is the offset where the position data begins in the buffer.
    glVertexAttribPointer(vpos_location, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), (void*)0);
    glEnableVertexAttribArray(vpos_location);  // vertex attributes are disabled by default

    glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), (void*)(sizeof(float) * 2));
    glEnableVertexAttribArray(vcol_location);

    while (!glfwWindowShouldClose(window)) {
        float ratio;
        int width, height;
        mat4x4 m, p, mvp;

        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float)height;

        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);

        mat4x4_identity(m);
        mat4x4_rotate_Z(m, m, (float)glfwGetTime());
        mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
        mat4x4_mul(mvp, p, m);

        glUseProgram(program);  // activate the shader program

        glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat*)mvp);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);    // swap the buffers
        glfwPollEvents();           // poll IO events
    }

    glfwDestroyWindow(window);

    glfwTerminate();

    return 0;
}


#include "framework.h"
#include "utils.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "glm/ext.hpp"

#include <math.h>
#include <iterator>
#include <algorithm>
#include <functional>

#include "include/linmath.h"
#include "include/shader.h"

#include "AppGL.hpp"

// Class constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int MAX = 100;
const float DEFAULT = 20.0f;

// Class variables
float _zview = 0.5f;
float _aspect = 1.0f;
float _width = 0.0f;
float _height = 0.0f;
float _zoom = 1.0f;
float _anglex = 0.0f;
float _angley = 0.0f;
float _anglez = 0.0f;

float _wmin[3] = { 0.0, 0.0f, 0.0f };
float _wmax[3] = { 0.0f, 0.0f, 0.0f };
std::vector<std::vector<float>> _vPoints;   // vector list

// COCiter == Container of Containers Iterator
// Oiter == Output Iterator
template <class COCiter, class Oiter>
void flatten(COCiter start, COCiter end, Oiter dest) {
    while (start != end) {
        dest = std::copy(start->begin(), start->end(), dest);
        ++start;
    }
}


AppGL::AppGL() {
}

// Initialize OpenGL Graphics
void AppGL::init(void) {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);   // Set background color to black and opaque
    glClearDepth(1.0f);                     // Set background depth to farthest
    glEnable(GL_DEPTH_TEST);                // Enable depth testing for z-culling
    glDepthFunc(GL_LEQUAL);                 // Set the type of depth-test
    //glShadeModel(GL_SMOOTH);                // Enable smooth shading
    //glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);     // clear the window

    //glMatrixMode(GL_PROJECTION);
    //glLoadIdentity();                                       // reset the camera (unit modelview matrix)
    //glMatrixMode(GL_MODELVIEW);
    //glLoadIdentity();                                       // clear the matrix
    //glScalef(SCALE_FACTOR, SCALE_FACTOR, SCALE_FACTOR);     // scale x, y, z
}


void AppGL::error_callback(int error, const char* description) {
    //fprintf(stderr, "Error: %s\n", description);
    std::cout << "Error: " << description << std::endl;
}


// Display a few points to stdout (default is n=5)
void AppGL::print_vector(void) {
    std::cout << "print_vector:" << std::endl;
    for (std::vector<float> v : _vPoints) {
        std::cout << "(" << v[0] << ", " << v[1] << ", " << v[2] << ")" << std::endl;
    }
}


// Called by OpenGL when it detects a keyboard event (key is pressed)
void AppGL::process_input(GLFWwindow* window, int key, int scancode, int action, int mods) {
    unsigned char prev = 'Z';

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    switch (toupper(key)) {
    case 'L':  // Move the object left
        Move(Move_Direction::left);
        break;
    case 'R':  // Move the object right
        Move(Move_Direction::right);
        break;
    case 'U':  // Move the object up
        Move(Move_Direction::up);
        break;
    case 'D':  // Move the object down
        Move(Move_Direction::down);
        break;
    case 'I':  //  Move the object 'in' (increase the Z)
        Move(Move_Direction::in);
        print_vector();
        std::cout << std::endl;
        break;
    case 'O':  // Move the object 'out' (decrease the Z)
        Move(Move_Direction::out);
        print_vector();
        std::cout << std::endl;
        break;
    case 'X':   // Rotate about X-axis
        _anglex += 10.0f;
        Rotate(_anglex, Rotate_Axis::X);
        break;
    case 'Y':   // Rotate about Y-axis
        _angley += 10.0f;
        Rotate(_angley, Rotate_Axis::Y);
        break;
    case 'Z':   // Rotate about Z-axis
        _anglez += 10.0f;
        Rotate(_anglez, Rotate_Axis::Z);
        break;
    case '1':   // Reset to initial state
        Reset();
        break;
    case 'Q':   // Quit the program
        exit(0);
        break;
    case '2':  // zoom in
        if (prev == key)
            _zoom -= 0.05f;
        else
            _zoom = 1.0f - 0.05f;
        glScalef(_zoom, _zoom, 1.0f);
        break;
    case '3':  // zoom out
        if (prev == key)
            _zoom += 0.05f;
        else
            _zoom = 1.0f + 0.05f;
        glScalef(_zoom, _zoom, 1.0f);
        break;
    }
    prev = key;

    //glfwPostRedisplay();
}

// Called when OpenGL needs to update the display
void AppGL::display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   // Clear color and depth buffers

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //gluLookAt(0.0f, 0.0f, 3.0f,     // position of camera
    //          0.0f, 0.0f, -100.0f,     // point at which camera looks
    //          0.0f, 1.0f, 0.0f);    // "up" direction of camera

    // Draw lines
    glBegin(GL_LINE_STRIP);
    glColor3f(1.0f, 0.0f, 0.0f);    // red
    for (std::vector<float> v : _vPoints) {
        glVertex3f(v[0], v[1], v[2]);
    }
    glEnd();

    glFlush();  // force update of screen
}

void AppGL::resize(GLFWwindow* window, int width, int height) {
    // save current values to be used by other methods
    _width = width;
    _height = height;

    // Compute aspect ratio of the new window
    //if (height == 0) height = 1;                // To prevent divide by 0
    //float aspect = float(width) / float(height);

    // Set the viewport to cover the new window
    glViewport(0, 0, width, height);

    // Set the aspect ratio of the clipping volume to match the viewport
    //glMatrixMode(GL_PROJECTION);
    //glLoadIdentity();
    //gluPerspective(0.0f, aspect, 0.1f, 1000.0f);
}


int AppGL::ReadFile(std::string filename) {
    std::string line, sout;
    std::string chars_to_trim = ".,/ ";
    float vmin[] = { 0.0f, 0.0 };
    float vmax[] = { float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1) };
    char seps[] = ",\n";

    // Read from the text file
    std::ifstream f_in(filename);
    if (f_in.fail()) {
        std::cerr << "File open error.\n";
        return 1;
    }

    // Read file line by line
    _vPoints.clear();
    while (!f_in.eof()) {
        getline(f_in, line);   // read line
        std::vector<float> v = split(line);
        if (v.size() > 1) {  // ignore J line
            for (int i = 0; i < v.size(); i++) {
                if (v[i] <= _wmin[i])  _wmin[i] = v[i];
                if (v[i] >= _wmax[i])  _wmax[i] = v[i];
            }
            _vPoints.push_back(v);  // add point to vector list
        }
    }

    std::cout << "read_file:" << std::endl;

    std::cout << "vmin: (" << vmin[0] << ", " << vmin[1] << ") " << std::endl;
    std::cout << "vmax: (" << vmax[0] << ", " << vmax[1] << ") " << std::endl;
    std::cout << "wmin: (" << _wmin[0] << ", " << _wmin[1] << ", " << _wmin[2] << ") " << std::endl;
    std::cout << "wmax: (" << _wmax[0] << ", " << _wmax[1] << ", " << _wmax[2] << ") " << std::endl;

    f_in.close();   // Close the file

    float a[2] = { 0.0f, 0.0f };
    float b[2] = { 0.0f, 0.0f };
    a[0] = (vmax[0] - vmin[0]) / (_wmax[0] - _wmin[0]);
    a[1] = (vmax[1] - vmin[1]) / (_wmax[1] - _wmin[1]);
    b[0] = (vmin[0] * _wmax[0] - vmax[0] * _wmin[0]) / (_wmax[0] - _wmin[0]);
    b[0] = (vmin[1] * _wmax[1] - vmax[1] * _wmin[1]) / (_wmax[1] - _wmin[1]);

    // Display vector list
    glm::mat3 m;
    glm::vec3 mv;
    for (std::vector<float> &v : _vPoints) {
        // Normalize vector list
        m = glm::mat3(glm::vec3(a[0], 0.0f, 0.0f),
                      glm::vec3(0.0f, a[1], 0.0f),
                      glm::vec3(b[0], b[1], 1.0f));
        mv = m * glm::vec3(v[0], v[1], v[2]);
        v[0] = mv[0];
        v[1] = mv[1];
        v[2] = mv[2];
        std::cout << "(" << v[0] << ", " << v[1] << ", " << v[2] << ")" << std::endl;
    }
    std::cout << std::endl;

    return 0;
}


// Translation: left, right, up, down
void AppGL::Move(Move_Direction direction) {
    float Dx, Dy, Dz;
    Dx = Dy = Dz = 0.0f;
    std::vector<float> x_vector;

    switch (direction) {
    case Move_Direction::left:
        Dx = -DEFAULT;
        break;
    case Move_Direction::right:
        Dx = DEFAULT;
        break;
    case Move_Direction::up:
        Dy = DEFAULT;
        break;
    case Move_Direction::down:
        Dy = -DEFAULT;
        break;
    case Move_Direction::in:
        Dz = DEFAULT;
        break;
    case Move_Direction::out:
        Dz = -DEFAULT;
        break;
    }

    //xt::xarray<float> A
    //{{1.0f, 0.0f, 0.0f, Dx},
    // {0.0f, 1.0f, 0.0f, Dy},
    // {0.0f, 0.0f, 1.0f, Dz},
    // {0.0f, 0.0f, 0.0f, 1.0f}};

    //for (std::vector<float> &v : _vPoints) {
    //    xt::xarray<float> x0
    //    { v[0], v[1], v[2], 1.0f };

    //    auto x = xt::linalg::dot(A, xt::transpose(x0));
    //    //std::cout << "x: " << x << std::endl;

    //    v[0] = x(0);
    //    v[1] = x(1);
    //    v[2] = x(2);
    //}
}


// Rotation about x-, y-, or z-axis
void AppGL::Rotate(float angle, Rotate_Axis axis) {
    float Dx, Dy, Dz;
    Dx = Dy = Dz = 0.0f;
    std::vector<float> x_vector;

    switch (axis) {
    case Rotate_Axis::X:
        glRotatef(angle, 1, 0, 0);
        break;
    case Rotate_Axis::Y:
        glRotatef(angle, 0, 1, 0);
        break;
    case Rotate_Axis::Z:
        glRotatef(angle, 0, 0, 1);
        break;
    }
}

void AppGL::Reset() {
    // Set member variables to default values
    _zview = 0.5f;
    _aspect = 1.0f;
    _width = 0.0f;
    _height = 0.0f;
    _zoom = 1.0f;
    _anglex = 0.0f;
    _angley = 0.0f;
    _anglez = 0.0f;

    //GLint depth;
    //glGetIntegerv(GL_MODELVIEW_STACK_DEPTH, &depth);
    //std::cout << "GL_MODELVIEW_STACK_DEPTH: " << depth << std::endl;
    //glGetIntegerv(GL_PROJECTION_STACK_DEPTH, &depth);
    //std::cout << "GL_PROJECTION_STACK_DEPTH: " << depth << std::endl;

    ReadFile("pixa.dat");
    init();
    display();
}


int AppGL::Run(int argc, char** argv, std::string filename) {
    glfwSetErrorCallback(error_callback);

    // initialise GLFW
    if (glfwInit() != GL_TRUE) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // create window
    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "mp4", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);

    glfwSetKeyCallback(window, process_input);
    gladLoadGL();
    glfwSwapInterval(1);

    //glfwSetFramebufferSizeCallback(window, resize);  // register the resize function

    // initialize Glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        exit(EXIT_FAILURE);
    }

    //init();  // custom initialization

    glEnable(GL_DEPTH_TEST);

    //// flatten 2D vector
    //std::vector<float> flat;
    //flatten(_vPoints.begin(), _vPoints.end(), back_inserter(flat));

    //// convert vector to array
    //float* vertices = flat.data();

    // render loop
    float ratio;
    int width, height;
    while (!glfwWindowShouldClose(window)) {        
        //glfwGetFramebufferSize(window, &width, &height);
        //ratio = width / (float)height;

        //glViewport(0, 0, width, height);
        //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   // clear color and depth buffers

        display();

        glfwSwapBuffers(window);    // swap the buffers
        glfwPollEvents();           // poll IO events
    }

    glfwTerminate();    // cleanup resources

    return 0;
}

int AppGL::main_gl(int argc, char** argv) {
    // notify compiler that both types of I/O will be used
    std::ios::sync_with_stdio();

    std::string filename = "input/cube.dat";

    ReadFile(filename);
    Run(argc, argv, filename);

    return 0;
}


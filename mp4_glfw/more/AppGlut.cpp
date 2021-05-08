#include "framework.h"
#include "AppGL.hpp"
#include "utils.hpp"

#include "xtensor-blas/xlinalg.hpp"
#include <xtensor/xarray.hpp>

#include <functional>

/**
 * Passing C++ Member Function to C Callback
 */
template <typename T>
struct Callback;

template <typename Ret, typename... Params>
struct Callback<Ret(Params...)> {
    template <typename... Args>
    static Ret callback(Args... args) {
        return func(args...);
    }
    static std::function<Ret(Params...)> func;
};

template <typename Ret, typename... Params>
std::function<Ret(Params...)> Callback<Ret(Params...)>::func;

typedef void (*display_callback_t)(void);
typedef void (*keyboard_callback_t)(unsigned char, int, int);
typedef void (*reshape_callback_t)(int, int);


AppGL::AppGL() {
}


// Initialize OpenGL Graphics
void AppGL::init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);   // Set background color to black and opaque
    glClearDepth(1.0f);                     // Set background depth to farthest
    //glEnable(GL_DEPTH_TEST);                // Enable depth testing for z-culling
    //glDepthFunc(GL_LEQUAL);                 // Set the type of depth-test
    //glShadeModel(GL_SMOOTH);                // Enable smooth shading
    //glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);     // clear the window

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();                                       // reset the camera (unit modelview matrix)
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();                                       // clear the matrix
    glScalef(SCALE_FACTOR, SCALE_FACTOR, SCALE_FACTOR);     // scale x, y, z
}


// Display a few points to stdout (default is n=5)
void AppGL::print_vector(int n) {
    // Translate coordinates from World to Screen
    float x_ratio = (float(SCREEN_WIDTH) - 1.0f) / (2.0f * float(WORLD_SIZE));   // 639 / 2000 = 0.3195
    float y_ratio = (float(SCREEN_HEIGHT) - 1.0f) / (2.0f * float(WORLD_SIZE));  // 479 / 2000 = 0.2395
    float z_ratio = 1.0f / (float(WORLD_SIZE));
    float screen_x, screen_y, screen_z;

    std::cout << "print_vector:" << std::endl;

    int i = 0;
    for (std::vector<float> v : _vPoints) {
        screen_x = v[0] * x_ratio;
        screen_y = v[1] * y_ratio;
        screen_z = v[2] * z_ratio;
        glVertex3f(screen_x, screen_y, screen_z);
        if (i < n)
            std::cout << "(" << screen_x << ", " << screen_y << ", " << screen_z << ")" << std::endl;
        i++;
    }
}


// Called by OpenGL when it detects a keyboard event (key is pressed)
void AppGL::keyboard(unsigned char key, int x, int y) {
    unsigned char prev = 'Z';

    if (key == 27)  exit(0);  // 27 is the Escape key

    switch (toupper(key)) {
        case 'L':  // Move the object left
            move(Move_Direction::left);
            break;
        case 'R':  // Move the object right
            move(Move_Direction::right);
            break;
        case 'U':  // Move the object up
            move(Move_Direction::up);
            break;
        case 'D':  // Move the object down
            move(Move_Direction::down);
            break;
        case 'I':  //  Move the object 'in' (increase the Z)
            move(Move_Direction::in);
            print_vector();
            std::cout << std::endl;
            break;
        case 'O':  // Move the object 'out' (decrease the Z)
            move(Move_Direction::out);
            print_vector();
            std::cout << std::endl;
            break;
        case 'X':   // Rotate about X-axis
            _anglex += 10.0f;
            rotate(_anglex, Rotate_Axis::X);
            break;
        case 'Y':   // Rotate about Y-axis
            _angley += 10.0f;
            rotate(_angley, Rotate_Axis::Y);
            break;
        case 'Z':   // Rotate about Z-axis
            _anglez += 10.0f;
            rotate(_anglez, Rotate_Axis::Z);
            break;
        case '1':   // Reset to initial state
            reset();
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

    glutPostRedisplay();
}


void AppGL::reshape(int width, int height) {
    // save current values to be used by other methods
    _width = width;
    _height = height;

    // Compute aspect ratio of the new window
    //if (height == 0) height = 1;                // To prevent divide by 0
    //float aspect = float(width) / float(height);

    // Set the viewport to cover the new window
    glViewport(0, 0, width, height);

    // Set the aspect ratio of the clipping volume to match the viewport
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();                                 // reset the camera (unit modelview matrix)
    glOrtho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);   // unit cube
    glMatrixMode(GL_MODELVIEW);
}


// Called when OpenGL needs to update the display
void AppGL::display() {
    // Translate coordinates from World to Screen
    float x_ratio = (float(SCREEN_WIDTH) - 1.0f) / (2.0f * float(WORLD_SIZE));   // 639 / 2000 = 0.3195
    float y_ratio = (float(SCREEN_HEIGHT) - 1.0f) / (2.0f * float(WORLD_SIZE));  // 479 / 2000 = 0.2395
    float z_ratio = 1.0f / (float(WORLD_SIZE));
    float screen_x, screen_y, screen_z;


    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   // clear the window
    glColor3f(1.0f, 0.0f, 0.0f);    // red

    glMatrixMode(GL_MODELVIEW);

    gluLookAt(0.0f, 0.0f, 5.0f,     // position of camera
        0.0f, 0.0f, 0.0f,           // point at which camera looks
        0.0f, 1.0f, 0.0f);          // "up" direction of camera

    // Graph points
    glBegin(GL_LINE_STRIP);  // draw lines
    for (std::vector<float> v : _vPoints) {
        screen_x = v[0] * x_ratio;
        screen_y = v[1] * y_ratio;
        screen_z = v[2] * z_ratio;
        glVertex3f(screen_x, screen_y, screen_z);
        //print_vector();
        //std::cout << std::endl;
    }
    glEnd();

    glFlush();  // force update of screen
}


int AppGL::read_file(std::string filename) {
    std::string line, sout;
    std::string chars_to_trim = ".,/ ";

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
        if (v.size()) {  // ignore J line
            _vPoints.push_back(v);  // add point to vector list
        }
    }

    f_in.close();   // Close the file

    std::cout << "read_file:" << std::endl;

    // Display vector list to command line
    for (std::vector<float> v : _vPoints) {
        std::cout << "(" << v[0] << ", " << v[1] << ", " << v[2] << ") " << std::endl;
    }
    std::cout << std::endl;

    return 0;
}


// Translation: left, right, up, down
void AppGL::move(Move_Direction direction) {
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

    xt::xarray<float> A
    {{1.0f, 0.0f, 0.0f, Dx},
     {0.0f, 1.0f, 0.0f, Dy},
     {0.0f, 0.0f, 1.0f, Dz},
     {0.0f, 0.0f, 0.0f, 1.0f}};

    for (std::vector<float> &v : _vPoints) {
        xt::xarray<float> x0
        { v[0], v[1], v[2], 1.0f };

        auto x = xt::linalg::dot(A, xt::transpose(x0));
        //std::cout << "x: " << x << std::endl;

        v[0] = x(0);
        v[1] = x(1);
        v[2] = x(2);
    }
}


// Rotation about x-, y-, or z-axis
void AppGL::rotate(float angle, Rotate_Axis axis) {
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

void AppGL::reset() {
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

    read_file("pixa.dat");
    init();
    display();
}


int AppGL::run(int argc, char** argv, std::string filename) {
    // Get pointers to callback functions (class methods)
    // We can pass the function to C API that wants a standard function callback
    Callback<void(unsigned char, int, int)>::func = std::bind(&AppGL::keyboard,
                                                              this,
                                                              std::placeholders::_1,
                                                              std::placeholders::_2,
                                                              std::placeholders::_3);
    keyboard_callback_t keyboard = static_cast<keyboard_callback_t>(Callback<void(unsigned char, int, int)>::callback);

    Callback<void(void)>::func = std::bind(&AppGL::display, this);
    display_callback_t display = static_cast<display_callback_t>(Callback<void(void)>::callback);

    Callback<void(int, int)>::func = std::bind(&AppGL::reshape,
                                               this,
                                               std::placeholders::_1,
                                               std::placeholders::_2);
    reshape_callback_t reshape = static_cast<reshape_callback_t>(Callback<void(int, int)>::callback);

    // Get a method pointer
    //void (AppGL::*pDisplay)(void) = &AppGL::display;
    //void (AppGL::*pKeyboard)(unsigned char, int, int) = &AppGL::keyboard;

    //auto display = std::mem_fn(&AppGL::display);
    //auto keyboard = std::mem_fn(&AppGL::display);

    glutInit(&argc, argv);               // initialise opengl
    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);  // Set the window size
    glutInitWindowPosition(100, 100);    // set the window position
    glutCreateWindow(filename.c_str());  // create the window
    init();                              // custom initialization
    glutDisplayFunc(display);            // register the display function
    glutReshapeFunc(reshape);            // register the reshape function
    glutKeyboardFunc(keyboard);          // register the keyboard function
    glutMainLoop();                      // enter the opengl main loop

    return 0;
}

int AppGL::main_gl(int argc, char** argv) {
    // notify compiler that both types of I/O will be used
    std::ios::sync_with_stdio();

    std::string filename = "pixa.dat";

    read_file(filename);
    run(argc, argv, filename);

    return 0;
}


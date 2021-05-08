#include "framework.h"
#include "utils.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "glm/ext.hpp"

#include <functional>

#include "include/linmath.h"
#include "AppGL.h"

// Class constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const float SCALE_FACTOR = 0.0003f;
const int MAX = 100;
const float DEFAULT = 20.0f;

// Class variables
float _scale = 1.0f;
//float _width = 0.0f;
//float _height = 0.0f;

std::vector<std::vector<float>> _vWorld;     // vector list
std::vector<std::vector<float>> _vScreen;    // vector list
std::vector<std::vector<float>> _vViewport;  // vector list

AppGL::AppGL() {
}


// Initialize OpenGL Graphics
void AppGL::init(void) {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);   // Set background color to black and opaque
    glClearDepth(1.0f);                     // Set background depth to farthest
    glEnable(GL_DEPTH_TEST);                // Enable depth testing for z-culling
    glDepthFunc(GL_LEQUAL);                 // Set the type of depth-test
    glShadeModel(GL_SMOOTH);                // Enable smooth shading
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
}

// Called by OpenGL when it detects a keyboard event (key is pressed)
void AppGL::keyboard(unsigned char key, int x, int y) {
    float angle[] = { 0.0f, 0.0f, 0.0f };
    float zoom = 1.0f;
    unsigned char prev = 'Z';

    if (key == 27)  exit(0);  // 27 is the Escape key

    switch (toupper(key)) {
        case 'L':  // Move the object leftr
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
            print_vector(_vScreen);
            std::cout << std::endl;
            break;
        case 'O':  // Move the object 'out' (decrease the Z)
            move(Move_Direction::out);
            print_vector(_vScreen);
            std::cout << std::endl;
            break;
        case 'X':   // Rotate about X-axis
            angle[0] += 10.0f;
            rotate(angle[0], Rotate_Axis::X);
            break;
        case 'Y':   // Rotate about Y-axis
            angle[1] += 10.0f;
            rotate(angle[1], Rotate_Axis::Y);
            break;
        case 'Z':   // Rotate about Z-axis
            angle[2] += 10.0f;
            rotate(angle[2], Rotate_Axis::Z);
            break;
        case '1':   // Reset to initial state
            reset();
            break;
        case 'Q':   // Quit the program
            exit(0);
            break;
        case '2':  // zoom in
            if (prev == key)
                zoom -= 0.05f;
            else
                zoom = 1.0f - 0.05f;
            glScalef(zoom, zoom, 1.0f);
            break;
        case '3':  // zoom out
            if (prev == key)
                zoom += 0.05f;
            else
                zoom = 1.0f + 0.05f;
            glScalef(zoom, zoom, 1.0f);
            break;
    }
    prev = key;

    glutPostRedisplay();
}

// Called when OpenGL needs to update the display
void AppGL::display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
    glMatrixMode(GL_MODELVIEW);     // Select the model-view matrix
    Draw();
    glutSwapBuffers();  // Swap front/back frame buffers (double buffering)
}

void AppGL::resize(int width, int height) {
    // Compute aspect ratio of the new window
    if (height == 0) height = 1;                // To prevent divide by 0
    float aspect = (float)width / (float)height;

    // Set the viewport to cover the new window
    glViewport(0, 0, width, height);

    float fov = 30.0f;
    float zNear = 0.1f;
    float zFar = float(width) * 10.0;

    // Set the aspect ratio of the clipping volume to match the viewport
    //glMatrixMode(GL_PROJECTION);  // Select the Projection matrix
    //glLoadIdentity();             // Reset
    //gluPerspective(30.0f, aspect, zNear, zFar); 
}

void AppGL::Draw(void) {
    float scale = 0.5f;

    //glLoadIdentity();                         // Reset the model-view matrix 
    //glTranslatef(0.0f, 0.0f, 0.0f);  // Move left and into the screen
    //glScalef(scale, scale, scale);

    // Position the camera on the Z axis at (0.0, 0.0, 0.5)
    // looking towards the origin
    gluLookAt(0.0, 0.0, 10.0,       // position of camera
        0.0, 0.0, 0.0,       // point at which camera looks
        0.0, 1.0, 0.0);      // up direction of camera

    // Draw lines
    glBegin(GL_LINE_STRIP);
        glColor3f(1.0f, 0.0f, 0.0f);    // red
        for (std::vector<float> v : _vScreen) {
            //glVertex2f(v[0], v[1]);
            glVertex3f(v[0], v[1], 1.0f);
            print_vector(v);
        }
    glEnd();
}

void AppGL::DrawCube(void) {
    glLoadIdentity();                    // Reset the model-view matrix
    glTranslatef(-5.0f, -5.0f, -40.0f);  // Move right and into the screen
    glScalef(0.4f, 0.4f, 1.0f);

    // Draw lines
    glBegin(GL_LINE_STRIP);
        glColor3f(1.0f, 0.0f, 0.0f);    // red
        for (std::vector<float> v : _vScreen) {
            glVertex3f(v[0], v[1], v[2]);
            print_vector(v);
        }
    glEnd();
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

    for (std::vector<float> &v : _vScreen) {
        glm::mat4 M = glm::mat4(glm::vec4(1.0f, 0.0f, 0.0f, Dx),
            glm::vec4(0.0f, 1.0f, 0.0f, Dy),
            glm::vec4(0.0f, 0.0f, 1.0f, Dz),
            glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
        glm::vec4 x = glm::transpose(M) * glm::vec4(v[0], v[1], v[2], 1.0f);
        copy_to_vector(x, v);
    }
}


// Rotation about x-, y-, or z-axis
void AppGL::rotate(float angle, Rotate_Axis axis) {
    switch (axis) {
        case Rotate_Axis::X:
            //glRotatef(angle, 1, 0, 0);
            for (std::vector<float>& v : _vScreen) {
                glm::mat4 M = glm::mat4(1.0f);
                M = glm::rotate(M, glm::radians(angle), glm::vec3(1.0, 0.0, 0.0));
                glm::vec4 x = M * glm::vec4(v[0], v[1], v[2], 1.0f);
                copy_to_vector(x, v);
            }
            break;
        case Rotate_Axis::Y:
            //glRotatef(angle, 0, 1, 0);
            for (std::vector<float>& v : _vScreen) {
                glm::mat4 M = glm::mat4(1.0f);
                M = glm::rotate(M, glm::radians(angle), glm::vec3(0.0, 1.0, 0.0));
                glm::vec4 x = glm::transpose(M) * glm::vec4(v[0], v[1], v[2], 1.0f);
                copy_to_vector(x, v);
            }
            break;
        case Rotate_Axis::Z:
            //glRotatef(angle, 0, 0, 1);
            for (std::vector<float>& v : _vScreen) {
                glm::mat4 M = glm::mat4(1.0f);
                M = glm::rotate(M, glm::radians(angle), glm::vec3(0.0, 0.0, 1.0));
                glm::vec4 x = glm::transpose(M) * glm::vec4(v[0], v[1], v[2], 1.0f);
                copy_to_vector(x, v);
            }
            break;
    }

}

void AppGL::reset(void) {
    read_file("input/pixa.dat");
    world_to_screen();
    glutSwapBuffers(); 
}


int AppGL::read_file(std::string filename) {
    char seps[] = ",\n";
    std::string line, sout;
    std::string chars_to_trim = ".,/ ";

    // Read from the text file
    std::ifstream f_in(filename);
    if (f_in.fail()) {
        std::cerr << "File open error.\n";
        return 1;
    }

    // Read file line by line
    _vWorld.clear();
    while (!f_in.eof()) {
        getline(f_in, line);   // read line
        std::vector<float> v = split(line);
        if (v.size() > 0) {  // ignore J line
            _vWorld.push_back(v);  // add point to vector list
        }
    }
    f_in.close();   // Close the file

    return 0;
}

int AppGL::world_to_screen(void) {
    float vmin[] = { 0.0f, 0.0f, 0.0f };
    float vmax[] = { float(SCREEN_WIDTH - 10),
                     float(SCREEN_HEIGHT - 10),
                     float(SCREEN_HEIGHT - 10) };

    std::vector<float> vinit = _vWorld[0];

    float wmin[] = { vinit[0], vinit[1], vinit[2] };
    float wmax[] = { vinit[0], vinit[1], vinit[2] };

    _vScreen.clear();
    for (std::vector<float> v : _vWorld) {
        // find min/max values
        for (int i = 0; i < 3; i++) {
            if (v[i] <= wmin[i])  wmin[i] = v[i];
            if (v[i] >= wmax[i])  wmax[i] = v[i];
        }
        _vScreen.push_back(v);  // add to vector list
    }

    std::cout << "world_to_screen:" << std::endl;
    print_array(vmin, "vmin: ");
    print_array(vmax, "vmax: ");
    print_array(wmin, "wmin: ");
    print_array(wmax, "wmax: ");

    //_scale = 1.0 / wmax[0];

    // Convert world coords to screen coords
    float S[] = { 0.0f, 0.0f, 0.0f };
    for (int i = 0; i < 3; i++) {
        S[i] = (vmax[i] - vmin[i]) / (wmax[i] - wmin[i]);
    }
    print_array(S, "   S: ");

    for (std::vector<float> &v : _vScreen) {
        for (int i = 0; i < 3; i++) {
            v[i] = vmin[i] + (v[i] - wmin[i]) * S[i];
        }
        print_vector(v);
    }
    std::cout << std::endl;

    return 0;
}


int AppGL::window_to_viewport(void) {
    float vmin[] = { 0.0f, 0.0f, 0.0f };
    float vmax[] = { float(SCREEN_WIDTH - 10),
                     float(SCREEN_HEIGHT - 10),
                     float(SCREEN_HEIGHT - 10) };

    std::vector<float> vinit = _vWorld[0];

    float wmin[] = { vinit[0], vinit[1], vinit[2] };
    float wmax[] = { vinit[0], vinit[1], vinit[2] };

    _vScreen.clear();
    for (std::vector<float> v : _vWorld) {
        // find min/max values
        for (int i = 0; i < 3; i++) {
            if (v[i] <= wmin[i])  wmin[i] = v[i];
            if (v[i] >= wmax[i])  wmax[i] = v[i];
        }
        _vScreen.push_back(v);  // add to vector list
    }

    std::cout << "window_to_viewport:" << std::endl;
    print_array(vmin, "vmin: ");
    print_array(vmax, "vmax: ");
    print_array(wmin, "wmin: ");
    print_array(wmax, "wmax: ");

    //for (std::vector<float>& v : _vScreen) {
    //    print_vector(v);
    //}

    // Window to viewport mapping
    float a[2] = { 0.0f, 0.0f };
    float b[2] = { 0.0f, 0.0f };
    a[0] = (vmax[0] - vmin[0]) / (wmax[0] - wmin[0]);
    a[1] = (vmax[1] - vmin[1]) / (wmax[1] - wmin[1]);
    b[0] = (vmin[0] * wmax[0] - vmax[0] * wmin[0]) / (wmax[0] - wmin[0]);
    b[1] = (vmin[1] * wmax[1] - vmax[1] * wmin[1]) / (wmax[1] - wmin[1]);

    glm::mat3 m = glm::mat3(1.0f);  // identity matrix
    glm::vec3 mv;
    for (std::vector<float>& v : _vScreen) {
        m = glm::mat3(glm::vec3(a[0], 0.0f, 0.0f),
            glm::vec3(0.0f, a[1], 0.0f),
            glm::vec3(b[0], b[1], 1.0f));
        mv = m * glm::vec3(v[0], v[1], 1.0f);
        //std::cout << glm::to_string(mv) << std::endl;
        copy_to_vector(mv, v);
        //print_vector(v);
    }
    std::cout << std::endl;

    return 0;
}


int AppGL::run(int argc, char** argv, std::string filename) {
    glutInit(&argc, argv);               // initialise opengl
    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);  // Set the window size
    glutInitWindowPosition(300, 300);    // set the window position
    glutCreateWindow(filename.c_str());  // create the window

    glutDisplayFunc(display);            // register the display function
    glutReshapeFunc(resize);             // register the reshape function
    glutKeyboardFunc(keyboard);          // register the keyboard function

    init();

    glutMainLoop();                      // enter the opengl main loop

    return 0;
}

int AppGL::main_gl(int argc, char** argv) {
    // notify compiler that both types of I/O will be used
    std::ios::sync_with_stdio();

    std::string filename = "input/pixa.dat";

    read_file(filename);
    //world_to_screen();
    window_to_viewport();

    run(argc, argv, filename);

    return 0;
}


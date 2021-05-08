#include "framework.h"
#include "utils.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "glm/ext.hpp"

#include "Matrix.h"
#include "AppGL.h"

// Class constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const float SCALE_FACTOR = 0.0003f;
const int MAX = 100;

// Class variables
float _width = 1.0;
float _height = 1.0;
float _aspect = 1.0f;
float _zoom = 1.0f;
float _scale = 1.0f;
std::string _filename = "input/pixa.dat";

// This could be consolidated to a single vector
// but this is easier to debug for now.
std::vector<std::vector<float>> _vWorld;        // vector list for world coords
std::vector<std::vector<float>> _vScreen;       // vector list for screen coords
std::vector<std::vector<float>> _vViewport;     // vector list for viewport coords 

AppGL::AppGL() {
}


// Initialize OpenGL Graphics
void AppGL::init(void) {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
    glClearDepth(1.0f);                   // Set background depth to farthest
    glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
    glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
    glShadeModel(GL_SMOOTH);   // Enable smooth shading
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
}

// Called by OpenGL when it detects a keyboard event (key is pressed)
void AppGL::keyboard(unsigned char key, int x, int y) {
    float angle[] = { 0.0f, 0.0f, 0.0f }; 
    unsigned char prev = 'Z';

    if (key == 27)  exit(0);  // 27 is the Escape key

    switch (toupper(key)) {
        case 'L':  // Move the object leftr
            translate(Move_Direction::left);
            break;
        case 'R':  // Move the object right
            translate(Move_Direction::right);
            break;
        case 'U':  // Move the object up
            translate(Move_Direction::up);
            break;
        case 'D':  // Move the object down
            translate(Move_Direction::down);
            break;
        case 'I':  // Move the object 'in' (increase Z)
            if (prev == key)
                _zoom += 0.05f;
            else
                _zoom = 1.0f + 0.05f;
            scale(Move_Direction::in);
            print_vector(_vScreen);
            std::cout << std::endl;
            break;
        case 'O':  // Move the object 'out' (decrease Z)
            if (prev == key)
                _zoom -= 0.05f;
            else
                _zoom = 1.0f - 0.05f;
            scale(Move_Direction::out);
            print_vector(_vScreen);
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
        // Additional functionality
        case '4':   // elevate xy-plane (front view)
            elevate(Rotate_Axis::Z);
            break;
        case '5':   // elevate yz-plane (side view)
            elevate(Rotate_Axis::X);
            break;
        case '6':   // elevate xz-plane (top view)
            elevate(Rotate_Axis::Y);
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
    // Save current values to be used by other methods
    _width = width;
    _height = height;

    // Compute aspect ratio of the new window
    if (height == 0) height = 1;                // To prevent divide by 0
    float aspect = (float)width / (float)height;

    // Set the viewport to cover the new window
    glViewport(0, 0, width, height);

    float fov = 30.0f;
    float zNear = 0.1f;
    float zFar = float(width) * 5.0;

    //glm::ortho(0.0f, float(SCREEN_WIDTH), 0.0f, float(SCREEN_HEIGHT), 0.1f, 100.0f);

    //for (std::vector<float>& v : _vScreen) {
    //    glm::mat4 M = glm::perspective(glm::radians(30.0f), aspect, 0.1f, 100.0f);
    //    glm::vec4 x = glm::transpose(M) * glm::vec4(v[0], v[1], v[2], 1.0f);
    //    copy_to_vector(x, v);
    //}

    // Set the aspect ratio of the clipping volume to match the viewport
    //glMatrixMode(GL_PROJECTION);                // Select the projection matrix
    //glLoadIdentity();                           // Reset matrix
    //gluPerspective(fov, aspect, zNear, zFar);   // fovy, aspect, zNear, and zFar
}


// The function is called by display so we are in model-view matrix mode
void AppGL::Draw(void) {
    float scale = 0.5f;

    glLoadIdentity();  // Reset the model-view matrix 
    glTranslatef(-0.5, -0.4f, -0.5);  // Move left and into the screen
    //glScalef(scale, scale, scale);

    // Draw lines
    glBegin(GL_LINE_STRIP);
    glColor3f(1.0f, 0.0f, 0.0f);    // red
    for (std::vector<float> v : _vScreen) {
        glVertex3f(v[0], v[1], v[2]);
    }
    glEnd();
}


// The function is called by display so we are in model-view matrix mode
void AppGL::Zoom(float scale) {
    glLoadIdentity();  // Reset the model-view matrix 
    glScalef(scale, scale, scale);

    // Draw lines
    glBegin(GL_LINE_STRIP);
        glColor3f(1.0f, 0.0f, 0.0f);    // red
        for (std::vector<float> v : _vScreen) {
            glVertex3f(v[0], v[1], v[2]);
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
void AppGL::translate(Move_Direction direction) {
    float Dx, Dy, Dz;
    Dx = Dy = Dz = 0.0f;
    float delta = 0.1f;
    std::vector<float> x_vector;

    switch (direction) {
        case Move_Direction::left:
            Dx = -delta;
            break;
        case Move_Direction::right:
            Dx = delta;
            break;
        case Move_Direction::up:
            Dy = delta;
            break;
        case Move_Direction::down:
            Dy = -delta;
            break;
        default:
            return;
            break;
    }

    for (std::vector<float>& v : _vScreen) {
        Mat4 M = Mat4(Vec4(1.0f, 0.0f, 0.0f, Dx),
            Vec4(0.0f, 1.0f, 0.0f, Dy),
            Vec4(0.0f, 0.0f, 1.0f, Dz),
            Vec4(0.0f, 0.0f, 0.0f, 1.0f));
        Mat4 tm = M.transpose();
        Vec4 x = Vec4(v[0], v[1], v[2], 1.0f);        
        x = tm * x;
        copy_to_vector(x, v);
    }

    //for (std::vector<float> &v : _vScreen) {
    //    glm::mat4 M = glm::mat4(glm::vec4(1.0f, 0.0f, 0.0f, Dx),
    //                            glm::vec4(0.0f, 1.0f, 0.0f, Dy),
    //                            glm::vec4(0.0f, 0.0f, 1.0f, Dz),
    //                            glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

    //    glm::vec4 x = glm::transpose(M) * glm::vec4(v[0], v[1], v[2], 1.0f);

    //    // The default matrix layout in GLM is column-major ordering
    //    x = glm::transpose(M) * glm::vec4(v[0], v[1], v[2], _zoom);

    //    copy_to_vector(x, v);
    //}
}

// Zoom in / out
void AppGL::scale(Move_Direction direction) {
    float Dx, Dy, Dz;
    Dx = Dy = Dz = 0.0f;
    float delta = 0.1f;
    std::vector<float> x_vector;

    switch (direction) {
        case Move_Direction::in:
            Dz = _zoom;
            break;
        case Move_Direction::out:
            Dz = -_zoom;
            break;
        default:
            return;
            break;
    }

    for (std::vector<float>& v : _vScreen) {
        Mat4 M = Mat4(Vec4(_zoom, 0.0f, 0.0f, 0.0f),
                      Vec4(0.0f, _zoom, 0.0f, 0.0f),
                      Vec4(0.0f, 0.0f, _zoom, 0.0f),
                      Vec4(0.0f, 0.0f, 0.0f, 1.0f));
        Mat4 tm = M.transpose();
        Vec4 x = Vec4(v[0], v[1], v[2], _zoom);
        x = tm * x;
        copy_to_vector(x, v);
    }

    //for (std::vector<float>& v : _vScreen) {
    //    glm::mat4 M = glm::mat4(glm::vec4(_zoom, 0.0f, 0.0f, 0.0f),
    //                            glm::vec4(0.0f, _zoom, 0.0f, 0.0f),
    //                            glm::vec4(0.0f, 0.0f, _zoom, 0.0f),
    //                            glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
    //    glm::vec4 x = glm::transpose(M) * glm::vec4(v[0], v[1], v[2], 1.0f);
    //    // The default matrix layout in GLM is column-major ordering
    //    x = glm::transpose(M) * glm::vec4(v[0], v[1], v[2], _zoom);
    //    copy_to_vector(x, v);
    //}
}


// Rotate about x-, y-, or z-axis
void AppGL::rotate(float angle, Rotate_Axis axis) {
    switch (axis) {
        case Rotate_Axis::X:
            //glRotatef(angle, 1, 0, 0);
            for (std::vector<float>& v : _vScreen) {
                Mat4 M = Mat4();
                M = M.rotateX(angle);
                Mat4 tm = M.transpose();
                Vec4 x = Vec4(v[0], v[1], v[2], 1.0f);
                x = tm * x;
                copy_to_vector(x, v);
            }
            //for (std::vector<float>& v : _vScreen) {
            //    glm::mat4 M = glm::mat4(1.0f);
            //    M = glm::rotate(M, glm::radians(angle), glm::vec3(1.0, 0.0, 0.0));
            //    glm::vec4 x = glm::transpose(M) * glm::vec4(v[0], v[1], v[2], 1.0f);
            //    copy_to_vector(x, v);
            //}
            break;
        case Rotate_Axis::Y:
            for (std::vector<float>& v : _vScreen) {
                Mat4 M = Mat4();
                M = M.rotateY(angle);
                Mat4 tm = M.transpose();
                Vec4 x = Vec4(v[0], v[1], v[2], 1.0f);
                x = tm * x;
                copy_to_vector(x, v);
            }
            break;
        case Rotate_Axis::Z:
            for (std::vector<float>& v : _vScreen) {
                Mat4 M = Mat4();
                M = M.rotateZ(angle);
                Mat4 tm = M.transpose();
                Vec4 x = Vec4(v[0], v[1], v[2], 1.0f);
                x = tm * x;
                copy_to_vector(x, v);
            }
            break;
    }
}


// Show elevation view
void AppGL::elevate(Rotate_Axis axis) {
    switch (axis) {
        // Elevation in yz-plane (project onto the plane x=0)
        case Rotate_Axis::X:
            reset();
            for (std::vector<float>& v : _vScreen) {
                glm::mat4 M = glm::mat4(glm::vec4(0.0, 0.0, 0.0, 0.0),
                                        glm::vec4(0.0, 1.0, 0.0, 0.0),
                                        glm::vec4(0.0, 0.0, 1.0, 0.0),
                                        glm::vec4(0.0, 0.0, 0.0, 1.0));
                glm::vec4 x = glm::transpose(M) * glm::vec4(v[0], v[1], v[2], 1.0);
                v[0] = x[1];
                v[1] = x[2];
                v[2] = 0.0;
            }
            break;
        // Elevation in xz-plane (project onto the plane y=0)
        case Rotate_Axis::Y:
            reset();
            for (std::vector<float>& v : _vScreen) {
                glm::mat4 M = glm::mat4(glm::vec4(1.0, 0.0, 0.0, 0.0),
                                        glm::vec4(0.0, 0.0, 0.0, 0.0),
                                        glm::vec4(0.0, 0.0, 1.0, 0.0),
                                        glm::vec4(0.0, 0.0, 0.0, 1.0));
                glm::vec4 x = M * glm::vec4(v[0], v[1], v[2], 1.0);
                v[0] = x[0];
                v[1] = x[2];
                v[2] = 0.0;
            }
            break;
        // Elevation in xy-plane (project onto the plane z=0 - default)
        case Rotate_Axis::Z:
            reset();
            for (std::vector<float>& v : _vScreen) {
                glm::mat4 M = glm::mat4(glm::vec4(1.0, 0.0, 0.0, 0.0),
                                        glm::vec4(0.0, 1.0, 0.0, 0.0),
                                        glm::vec4(0.0, 0.0, 0.0, 0.0),
                                        glm::vec4(0.0, 0.0, 0.0, 1.0));
                glm::vec4 x = glm::transpose(M) * glm::vec4(v[0], v[1], v[2], 1.0);
                v[0] = x[0];
                v[1] = x[1];
                v[2] = 0.0;
            }
            break;
    }
}


// We could also compute and save the inverse matrices
// glm::mat4 inv = glm::inverse(M);
void AppGL::reset(void) {
    // Reset class variables
    _aspect = 1.0f;
    _zoom = 1.0f;

    read_file(_filename);
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

// Convert World coords to Screen coords
// then normalize coords.
int AppGL::world_to_screen(void) {
    float vmin[] = { 0.0f, 0.0f, 0.0f };
    float vmax[] = { float(SCREEN_WIDTH - 1),
                     float(SCREEN_HEIGHT - 1),
                     float(std::max(SCREEN_WIDTH, SCREEN_HEIGHT) - 1) };

    std::vector<float> vinit = _vWorld[0];

    float wmin[] = { vinit[0], vinit[1], vinit[2] };
    float wmax[] = { vinit[0], vinit[1], vinit[2] };

    _vScreen.clear();
    for (std::vector<float> v : _vWorld) {
        // find min/max values
        for (int i = 0; i < v.size(); i++) {
            if (v[i] <= wmin[i])  wmin[i] = v[i];
            if (v[i] >= wmax[i])  wmax[i] = v[i];
        }
        _vScreen.push_back(v);  // add to vector list
    }

    std::cout << "read_file:" << std::endl;
    print_array(vmin, "vmin: ");
    print_array(vmax, "vmax: ");
    print_array(wmin, "wmin: ");
    print_array(wmax, "wmax: ");

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
    }

    // Convert to normalized device coordinates (NDC)
    // since OpenGL expects all the vertices to be in NDC.
    for (std::vector<float>& v : _vScreen) {
        for (int i = 0; i < 3; i++) {
            v[i] = (v[i] - vmin[0]) / (vmax[0] - vmin[0]);
        }
        print_vector(v);
    }
    std::cout << std::endl;

    return 0;
}


// Window to Viewport Mapping
int AppGL::window_to_viewport(void) {
    float vmin[] = { 0.0f, 0.0f };
    float vmax[] = { float(SCREEN_WIDTH - 1),
                     float(SCREEN_HEIGHT - 1) };
    float wmin[] = { 0.0f, 0.0f };
    float wmax[] = { 0.0f, 0.0f };

    std::vector<float> vinit = _vScreen[0];
    wmin[0] = vinit[0];
    wmin[1] = vinit[1];
    wmax[0] = vinit[0];
    wmax[1] = vinit[1];

    _vViewport.clear();
    for (std::vector<float> v : _vScreen) {
        // find min/max values
        for (int i = 0; i < v.size(); i++) {
            if (v[i] <= wmin[i])  wmin[i] = v[i];
            if (v[i] >= wmax[i])  wmax[i] = v[i];
        }
        _vViewport.push_back(v);  // add to vector list
    }

    std::cout << "window_to_viewport:" << std::endl;
    print_array(vmin, "vmin: ");
    print_array(vmax, "vmax: ");
    print_array(wmin, "wmin: ");
    print_array(wmax, "wmax: ");

    // Window to viewport mapping
    float a[2] = { 0.0f, 0.0f };
    float b[2] = { 0.0f, 0.0f };
    a[0] = (vmax[0] - vmin[0]) / (wmax[0] - wmin[0]);
    a[1] = (vmax[1] - vmin[1]) / (wmax[1] - wmin[1]);
    b[0] = (vmin[0] * wmax[0] - vmax[0] * wmin[0]) / (wmax[0] - wmin[0]);
    b[1] = (vmin[1] * wmax[1] - vmax[1] * wmin[1]) / (wmax[1] - wmin[1]);

    glm::mat3 m = glm::mat3(1.0f);  // identity matrix
    glm::vec3 mv;
    for (std::vector<float>& v : _vViewport) {
        m = glm::mat3(glm::vec3(a[0], 0.0f, 0.0f),
            glm::vec3(0.0f, a[1], 0.0f),
            glm::vec3(b[0], b[1], 1.0f));
        //std::cout << glm::to_string(m) << std::endl;
        mv = glm::transpose(m) * glm::vec3(v[0], v[1], 1.0);
        copy_to_vector(mv, v);
        print_vector(v);
    }
    std::cout << std::endl;

    return 0;
}


int AppGL::run(int argc, char** argv, std::string filename) {
    glutInit(&argc, argv);               // initialise opengl
    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);  // Set the window size
    glutInitWindowPosition(300, 300);    // set the window position
    glutCreateWindow(filename.c_str());  // create the window

    glutDisplayFunc(display);           // register display function
    glutReshapeFunc(resize);            // register reshape function
    glutKeyboardFunc(keyboard);         // register keyboard function
    init();

    glutMainLoop();                     // enter the opengl main loop

    return 0;
}

int AppGL::main_gl(int argc, char** argv) { 
    std::ios::sync_with_stdio();    // Notify compiler that both types of I/O will be used

    read_file(_filename);
    world_to_screen();
    run(argc, argv, _filename);

    return 0;
}


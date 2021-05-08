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
float _angle[] = { 0.0f, 0.0f, 0.0f };
float _aspect = 1.0f;
float _width = 0.0f;
float _height = 0.0f;
float _zoom = 1.0f;
float _zview = 0.5f;

std::vector<std::vector<float>> _vPoints;   // vector list

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
            print_vector(_vPoints);
            std::cout << std::endl;
            break;
        case 'O':  // Move the object 'out' (decrease the Z)
            move(Move_Direction::out);
            print_vector(_vPoints);
            std::cout << std::endl;
            break;
        case 'X':   // Rotate about X-axis
            _angle[0] += 10.0f;
            rotate(_angle[0], Rotate_Axis::X);
            break;
        case 'Y':   // Rotate about Y-axis
            _angle[1] += 10.0f;
            rotate(_angle[1], Rotate_Axis::Y);
            break;
        case 'Z':   // Rotate about Z-axis
            _angle[2] += 10.0f;
            rotate(_angle[2], Rotate_Axis::Z);
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

// Called when OpenGL needs to update the display
void AppGL::display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
    glMatrixMode(GL_MODELVIEW);     // Select the model-view matrix
    Draw();
    glutSwapBuffers();  // Swap front/back frame buffers (double buffering)
}

void AppGL::resize(int width, int height) {
    // save current values to be used by other methods
    _width = width;
    _height = height;

    // Compute aspect ratio of the new window
    if (height == 0) height = 1;                // To prevent divide by 0
    float aspect = (float)width / (float)height;

    // Set the viewport to cover the new window
    glViewport(0, 0, width, height);

    float fov = 30.0f;
    float fNear = 0.1f;
    float fFar = float(width) * 10.0;

    // Using GLM for the transformations
    //for (std::vector<float>& v : _vPoints) {
    //    glm::mat4 M = glm::mat4(1.0f);
    //    glm::vec4 x(v[0], v[1], v[2], 1.0f);
    //    M = glm::perspective(glm::radians(fov), aspect, fNear, fFar);
    //    x = glm::transpose(M) * x;
    //    copy_to_vector(x, v);
    //}

    // Set the aspect ratio of the clipping volume to match the viewport
    glMatrixMode(GL_PROJECTION);  // Select the Projection matrix
    glLoadIdentity();             // Reset
    gluPerspective(30.0f, aspect, 0.1, (float(width) * 2.0));  // fovy, aspect, zNear, and zFar
}

void AppGL::Draw(void) {
    float scale = 0.3f;

    glLoadIdentity();                        // Reset the model-view matrix                             
    glTranslatef(-100.0, -100.0, -800.0);  // Move left and into the screen
    glScalef(scale, scale, scale);

    // Using GLM for the transformations
    //for (std::vector<float>& v : _vPoints) {
    //    glm::mat4 M = glm::mat4(1.0f);
    //    glm::vec4 x(v[0], v[1], v[2], 1.0f);
    //    M = glm::translate(M, glm::vec3(-100.0f, -100.0f, -800.0f));
    //    M = glm::scale(M, glm::vec3(0.3f, 0.3f, 0.3f));
    //    x = M * x;
    //    copy_to_vector(x, v);
    //}

    // Draw lines
    glBegin(GL_LINE_STRIP);
    glColor3f(1.0f, 0.0f, 0.0f);    // red
    for (std::vector<float> v : _vPoints) {
        //glVertex2f(v[0], v[1]);
        glVertex3f(v[0], v[1], v[2]);
        //print_vector(v);
    }
    glEnd();
}

void AppGL::DrawCube(void) {
    glLoadIdentity();                    // Reset the model-view matrix
    glTranslatef(-5.0f, -5.0f, -40.0f);  // Move right and into the screen
    //glScalef(0.4f, 0.4f, 1.0f);

    // Draw lines
    glBegin(GL_LINE_STRIP);
        glColor3f(1.0f, 0.0f, 0.0f);    // red
        for (std::vector<float> v : _vPoints) {
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

    for (std::vector<float> &v : _vPoints) {
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
            for (std::vector<float>& v : _vPoints) {
                glm::mat4 M = glm::mat4(1.0f);
                M = glm::rotate(M, glm::radians(angle), glm::vec3(1.0, 0.0, 0.0));
                glm::vec4 x = M * glm::vec4(v[0], v[1], v[2], 1.0f);
                copy_to_vector(x, v);
            }
            break;
        case Rotate_Axis::Y:
            //glRotatef(angle, 0, 1, 0);
            for (std::vector<float>& v : _vPoints) {
                glm::mat4 M = glm::mat4(1.0f);
                M = glm::rotate(M, glm::radians(angle), glm::vec3(0.0, 1.0, 0.0));
                glm::vec4 x = glm::transpose(M) * glm::vec4(v[0], v[1], v[2], 1.0f);
                copy_to_vector(x, v);
            }
            break;
        case Rotate_Axis::Z:
            //glRotatef(angle, 0, 0, 1);
            for (std::vector<float>& v : _vPoints) {
                glm::mat4 M = glm::mat4(1.0f);
                M = glm::rotate(M, glm::radians(angle), glm::vec3(0.0, 0.0, 1.0));
                glm::vec4 x = glm::transpose(M) * glm::vec4(v[0], v[1], v[2], 1.0f);
                copy_to_vector(x, v);
            }
            break;
    }

}

void AppGL::reset(void) {
    // Reset class variables
    _zview = 0.5f;
    _aspect = 1.0f;
    _width = 0.0f;
    _height = 0.0f;
    _zoom = 1.0f;

    for (int i = 0; i < 3; i++) {
        _angle[i] = 0.0f;
        //_wmax[i] = 1.0f;
    }

    // Get the current size of a matrix stack
    //GLint depth;
    //glGetIntegerv(GL_MODELVIEW_STACK_DEPTH, &depth);
    //std::cout << "depth: " << depth;
    //glGetIntegerv(GL_PROJECTION_STACK_DEPTH, &depth);
    //std::cout << "depth: " << depth;

    read_file("input/pixa.dat");
    glutSwapBuffers(); 
}


// Create polygon list
int AppGL::create_polygon_list(void) {
    return 0;
}

int AppGL::read_file(std::string filename) {
    float vmin[] = { 0.0f, 0.0f, 0.0f };
    float vmax[] = { float(SCREEN_WIDTH - 1), 
                     float(SCREEN_HEIGHT - 1), 
                     std::max(SCREEN_WIDTH, SCREEN_HEIGHT) - 1.0f };
    float wmin[] = { 0.0f, 0.0f, 0.0f };
    float wmax[] = { 0.0f, 0.0f, 0.0f };
    float wall[] = { 0.0f, 0.0f, 0.0f };
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
    _vPoints.clear();
    while (!f_in.eof()) {
        getline(f_in, line);   // read line
        std::vector<float> v = split(line);
        if (v.size() > 0) {  // ignore J line
            for (int i = 0; i < v.size(); i++) {
                if (v[i] <= wmin[i])  wmin[i] = v[i];
                if (v[i] >= wmax[i])  wmax[i] = v[i];
            }
            _vPoints.push_back(v);  // add point to vector list
        }
    }
    f_in.close();   // Close the file

    std::cout << "read_file:" << std::endl;
    print_array(vmin, "vmin: ");
    print_array(vmax, "vmax: ");
    print_array(wmin, "wmin: ");
    print_array(wmax, "wmax: ");
 
    //for (int i = 0; i < 3; i++) {
    //    wall[i] = std::max(std::abs(wmin[i]), wmax[i]);
    //}
    //std::cout << "wall: (" << wall[0] << ", " << wall[1] << ", " << wall[2] << ") " << std::endl;

    // Convert world coords to screen coords
    float S[] = { 0.0f, 0.0f, 0.0f };
    for (int i = 0; i < 3; i++) {
        S[i] = (vmax[i] - vmin[i]) / (wmax[i] - wmin[i]);
    }
    print_array(S, "   S: ");
    for (std::vector<float> &v : _vPoints) {
        for (int i = 0; i < v.size(); i++) {
            v[i] = vmin[i] + (v[i] - wmin[i]) * S[i];
        }
        print_vector(v);
    }


    // Window to viewport mapping
    //float a[2] = { 0.0f, 0.0f };
    //float b[2] = { 0.0f, 0.0f };
    //a[0] = (vmax[0] - vmin[0]) / (wmax[0] - wmin[0]);
    //a[1] = (vmax[1] - vmin[1]) / (wmax[1] - wmin[1]);
    //b[0] = (vmin[0] * wmax[0] - vmax[0] * wmin[0]) / (wmax[0] - wmin[0]);
    //b[1] = (vmin[1] * wmax[1] - vmax[1] * wmin[1]) / (wmax[1] - wmin[1]);

    //glm::mat3 m;
    //glm::vec3 mv;
    //for (std::vector<float> &v : _vPoints) {
    //    m = glm::mat3(glm::vec3(a[0], 0.0f, 0.0f),
    //        glm::vec3(0.0f, a[1], 0.0f),
    //        glm::vec3(b[0], b[1], 1.0f));
    //    //std::cout << glm::to_string(m) << std::endl;
    //    print_vector(v);
    //    mv = m * glm::vec3(v[0], v[1], v[2]);
    //    copy_to_vector(mv, v);
    //    print_vector(v);
    //}
    //std::cout << std::endl;

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
    run(argc, argv, filename);

    return 0;
}


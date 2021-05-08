#include "framework.h"
#include "mp4.h"

//#include "CTensor.hpp"
#include "AppGL.hpp"
#include "HelloGLM.h"
#include "Triangle.h"
#include "RotateSquares.h"
#include "Simple.h"
#include "hello_triangle.h"
#include "hello_triangle_indexed.h"
#include "hello_rotate_triangle.h"
#include "camera_circle.h"
#include "camera_keyboard.h"

int main(int argc, char** argv) {
    // notify compiler that both types of I/O will be used
    std::ios::sync_with_stdio();

    //std::cout << "Hello!" << std::endl;

    //CTensor* ptr;
    //ptr = new CTensor();
    //ptr->main(argc, argv);

    AppGL* pGL;
    pGL->main_gl(argc, argv);

    //AppSDL *pApp = new AppSDL();
    //pApp->main(argc, argv);

    //Triangle::main_gl(argc, argv);
    //RotateSquares::main_gl(argc, argv);
    //Simple::main_gl(argc, argv);
    //AppGL::main_gl(argc, argv);

    //hello_triangle *ptr;
    //hello_rotate_triangle* ptr;
    //ptr->main_gl();

    //hello_triangle_indexed();
    //camera_circle();
    //camera_keyboard();

    //hello_glm();
    //la_review();

    system("pause");

    return 0;
}



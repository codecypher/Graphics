/*
 * mp4.cpp
 * Driver program for application
 */
#include "framework.h"
#include "mp4.hpp"

//#include "Example.h"
//#include "hello_glm.h"

#include "AppGL.h"

int main(int argc, char** argv) {
    // notify compiler that both types of I/O will be used
    std::ios::sync_with_stdio();

    //std::cout << "Hello!" << std::endl;

    //Example* ptr;
    //ptr->main_gl(argc, argv);

    //la_review();

    AppGL* pGL;
    pGL->main_gl(argc, argv);

    //AppGL3D* pGL;
    //pGL->main_gl(argc, argv);

    system("pause");

    return 0;
}



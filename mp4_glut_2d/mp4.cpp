/*
 * mp4.cpp
 * Driver program for application
 */
#include "framework.h"
#include "mp4.hpp"

#include "hello_glm.h"
#include "AppGL.h"

int main(int argc, char** argv) {
    // notify compiler that both types of I/O will be used
    std::ios::sync_with_stdio();

    //la_review();
    //la_scratch();

    AppGL* pGL;
    pGL->main_gl(argc, argv);

    system("pause");

    return 0;
}



/*
 * mp4.cpp
 * Driver program for application
 */
#include "framework.h"
#include "mp4.h"

//#include "hello_glm.h"
#include "AppGL.h"

int main(int argc, char** argv) {
    std::ios::sync_with_stdio();    // Notify compiler that both types of I/O will be used
        
    //la_review();

    AppGL* pGL;
    pGL->main_gl(argc, argv);

    system("pause");

    return 0;
}


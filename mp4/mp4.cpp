/*
 * mp4.cpp
 * Driver program for application
 */
#include "framework.h"
#include "mp4.h"

#include "Matrix.h"
#include "AppGL.h"

int main(int argc, char** argv) {
    std::ios::sync_with_stdio();    // Notify compiler that both types of I/O will be used
        
    //Mat3 M = Mat3(Vec3(0.0f, 1.0f, 4.0f),
    //              Vec3(1.0f, 0.0f, -3.0f),
    //              Vec3(2.0f, 3.0f, 8.0f));

    // C++ compiler creates a copy constructor and 
    // overloads assignment operator 
    // to perform shallow copy at compile time.
    //Mat3 Mbefore = M;  // using copy constructor
    //M.invert();

    // Check that M * Minv = I
    //std::cout << Mbefore << std::endl;
    //std::cout << M << std::endl;
    //std::cout << Mbefore * M << std::endl;

    AppGL* pGL;
    pGL->main_gl(argc, argv);

    system("pause");

    return 0;
}


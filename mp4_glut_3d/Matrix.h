/*
 * Matrix.h
 * This is a matrix class based on OpenGL Matrix Class
 * http://www.songho.ca/opengl/gl_matrix.html
 */
#pragma once

 // Demonstration of #include guard idiom.
#ifndef MATRIX_H_
#define MATRIX_H_

#include "Vector.h"

class Mat4 {
public:
    Mat4();  // init with identity
    Mat4(float m00, float m01, float m02, float m03, // 1st column
         float m04, float m05, float m06, float m07, // 2nd column
         float m08, float m09, float m10, float m11, // 3rd column
         float m12, float m13, float m14, float m15);// 4th column
    Mat4(Vec4 v1, Vec4 v2, Vec4 v3, Vec4 v4);

    Mat4& identity();
    Mat4& transpose();

    Mat4& translate(float x, float y, float z); 
    
    //Mat4& rotate(float angle, float x, float y, float z);
    
    Mat4& rotateX(float angle); 
    Mat4& rotateY(float angle);
    Mat4& rotateZ(float angle); 

    Mat4& scale(float scale);  
    Mat4& scale(float sx, float sy, float sz); 

    Vec4 multiply(Vec4& vec, Mat4& m);

    // operators
    Mat4  operator+(Mat4& rhs); 
    Mat4  operator-(Mat4& rhs); 
    Vec4  operator*(Vec4& rhs);
    Mat4  operator*(Mat4& rhs); 
    Mat4& operator*=(Mat4& rhs);

    float operator[](int index) const;    
    float& operator[](int index);

    // friends functions
    friend Mat4 operator-(Mat4& m);  
    friend Mat4 operator*(float scalar,  Mat4& m);
    //friend Vec4 operator*(Vec4& vec,  Mat4& m); 

private:
    float m[16];
    float tm[16];
};


#endif

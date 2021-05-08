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


class Mat3 {
public:
    // constructors
    Mat3();  // initialize with identity
    Mat3(float m0, float m1, float m2,          // 1st column
         float m3, float m4, float m5,          // 2nd column
         float m6, float m7, float m8);         // 3rd column
    Mat3(Vec3 v1, Vec3 v2, Vec3 v3);

    Mat3& identity();
    Mat3& transpose();                          // transpose
    Mat3& invert();

    // operators
    Mat3    operator+(const Mat3& rhs) const;      // add rhs
    Mat3    operator-(const Mat3& rhs) const;      // subtract rhs
    Mat3&   operator+=(const Mat3& rhs);           // add rhs and update this object
    Mat3&   operator-=(const Mat3& rhs);           // subtract rhs and update this object
    Vec3    operator*(const Vec3& rhs) const;      // multiplication: v' = M * v
    Mat3    operator*(const Mat3& rhs) const;      // multiplication: M3 = M1 * M2
    Mat3&   operator*=(const Mat3& rhs);           // multiplication: M1' = M1 * M2
    float   operator[](int index) const;            // subscript
    float&  operator[](int index);                   

    // friends functions
    friend Mat3 operator-(const Mat3& m);                   // unary operator
    friend Mat3 operator*(float scalar, const Mat3& m);     // pre-multiplication
    //friend Vec3 operator*(const Vec3& vec, const Mat3& m);
    friend std::ostream& operator<<(std::ostream& os, const Mat3& m);

private:
    float m[9];
    float tm[9];
};


class Mat4 {
public:
    Mat4();  // initialize with identity
    Mat4(float m00, float m01, float m02, float m03,    // 1st column
         float m04, float m05, float m06, float m07,    // 2nd column
         float m08, float m09, float m10, float m11,    // 3rd column
         float m12, float m13, float m14, float m15);   // 4th column
    Mat4(Vec4 v1, Vec4 v2, Vec4 v3, Vec4 v4);

    Mat4& identity();
    Mat4& transpose();
    Mat4& invert();

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
    friend std::ostream& operator<<(std::ostream& os, const Mat4& m);

private:
    float m[16];
    float tm[16];
};


#endif

/*
 * Vector.h
 * This is a vector class based on OpenGL Matrix Class
 * http://www.songho.ca/opengl/gl_matrix.html
 */
#pragma once

#ifndef VECTOR_H_
#define VECTOR_H_

struct Vec4 {
    float x;
    float y;
    float z;
    float w;

    Vec4();
    Vec4(float x, float y, float z, float w);

    float dot(Vec4& vec);          // dot product

    // operators
    Vec4    operator-();
    Vec4    operator+(Vec4& rhs);
    Vec4    operator-(Vec4& rhs);
    Vec4    operator*(Vec4& rhs);

    float   operator[](int index);

    friend Vec4 operator*(float a, Vec4 vec);
};


#endif
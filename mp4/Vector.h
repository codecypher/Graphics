/*
 * Vector.h
 * This is a vector class based on OpenGL Matrix Class
 * http://www.songho.ca/opengl/gl_matrix.html
 */
#pragma once

#ifndef VECTOR_H_
#define VECTOR_H_


struct Vec3 {
    float x;
    float y;
    float z;

    Vec3();
    Vec3(float x, float y, float z);

    float   length() const; 
    float   distance(const Vec3& vec) const;     // distance between two vectors
    Vec3&   normalize();
    float   dot(const Vec3& vec) const;          // dot product
    Vec3    cross(const Vec3& vec) const;        // cross product

    // operators
    Vec3    operator-();             // unary operator (negate)
    Vec3    operator+(Vec3& rhs);    // add rhs
    Vec3    operator-(Vec3& rhs);    // subtract rhs
    Vec3    operator*(float scale);  // scale
    Vec3    operator*(Vec3& rhs);    // multiplay each element
    float   operator[](int index);   // subscript
};


struct Vec4 {
    float x;
    float y;
    float z;
    float w;

    // constructors
    Vec4();
    Vec4(float x, float y, float z, float w);

    float dot(Vec4& vec);       // dot product

    // operators
    Vec4    operator-();
    Vec4    operator+(Vec4& rhs);
    Vec4    operator-(Vec4& rhs);
    Vec4    operator*(float scale); 
    Vec4    operator*(Vec4& rhs);
    float   operator[](int index);
};


#endif
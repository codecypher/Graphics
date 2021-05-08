#include <cmath>
#include "Vector.h"

//
// Vec3
//

Vec3::Vec3() {
    x = y = z = 0.0f;
}

Vec3::Vec3(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

Vec3 Vec3::operator-() {
    return Vec3(-x, -y, -z);
}

Vec3 Vec3::operator+(Vec3& rhs) {
    return Vec3(x + rhs.x, y + rhs.y, z + rhs.z);
}

Vec3 Vec3::operator-(Vec3& rhs) {
    return Vec3(x - rhs.x, y - rhs.y, z - rhs.z);
}

// scale
Vec3 Vec3::operator*(float a) {
    return Vec3(x * a, y * a, z * a);
}

// multiplay each element
Vec3 Vec3::operator*(Vec3& rhs) {
    return Vec3(x * rhs.x, y * rhs.y, z * rhs.z);
}


float Vec3::operator[](int index) {
    return (&x)[index];
}

float Vec3::length() const {
    return sqrtf(x * x + y * y + z * z);
}

float Vec3::distance(const Vec3& vec) const {
    return sqrtf((vec.x - x) * (vec.x - x) + (vec.y - y) * (vec.y - y) + (vec.z - z) * (vec.z - z));
}

Vec3& Vec3::normalize() {
    //@@const float EPSILON = 0.000001f;
    float xxyyzz = x * x + y * y + z * z;
    //@@if(xxyyzz < EPSILON)
    //@@    return *this; // do nothing if it is ~zero vector

    //float invLength = invSqrt(xxyyzz);
    float invLength = 1.0f / sqrtf(xxyyzz);
    x *= invLength;
    y *= invLength;
    z *= invLength;
    return *this;
}

float Vec3::dot(const Vec3& rhs) const {
    return (x * rhs.x + y * rhs.y + z * rhs.z);
}

Vec3 Vec3::cross(const Vec3& rhs) const {
    return Vec3(y * rhs.z - z * rhs.y, z * rhs.x - x * rhs.z, x * rhs.y - y * rhs.x);
}



//
// Vec4
//
Vec4::Vec4() {
    x = y = z = w = 0.0f;
}

Vec4::Vec4(float x, float y, float z, float w) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}

Vec4 Vec4::operator-() {
    return Vec4(-x, -y, -z, -w);
}

Vec4 Vec4::operator+(Vec4& rhs) {
    return Vec4(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w);
}

Vec4 Vec4::operator-(Vec4& rhs) {
    return Vec4(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w);
}

// scale
Vec4 operator*(float a, Vec4 vec) {
    return Vec4(a * vec.x, a * vec.y, a * vec.z, a * vec.w);
}

// multiplay each element
Vec4 Vec4::operator*(Vec4& rhs) {
    return Vec4(x * rhs.x, y * rhs.y, z * rhs.z, w * rhs.w);
}

float Vec4::operator[](int index) {
    return (&x)[index];
}

float Vec4::dot(Vec4& rhs) {
    return (x * rhs.x + y * rhs.y + z * rhs.z + w * rhs.w);
}




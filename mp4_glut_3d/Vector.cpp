#include "Vector.h"

Vec4::Vec4() {
    x = 0;
    y = 0;
    z = 0;
    w = 0;
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

Vec4 Vec4::operator*(Vec4& rhs) {
    return Vec4(x * rhs.x, y * rhs.y, z * rhs.z, w * rhs.w);
}

float Vec4::operator[](int index) {
    return (&x)[index];
}

float Vec4::dot(Vec4& rhs) {
    return (x * rhs.x + y * rhs.y + z * rhs.z + w * rhs.w);
}

Vec4 operator*(float a, Vec4 vec) {
    return Vec4(a * vec.x, a * vec.y, a * vec.z, a * vec.w);
}


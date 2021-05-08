#include <algorithm>
#include <cmath>
#include <iostream>
#include <iomanip>

#include "Matrix.h"

const float PI = 3.141593f;
const float EPSILON = 0.00001f;

//
// Mat3
//
Mat3::Mat3() {
    // initially identity matrix
    identity();
}


Mat3::Mat3(float m00, float m01, float m02, 
           float m03, float m04, float m05, 
           float m06, float m07, float m08) {
    m[0] = m00;
    m[1] = m01;
    m[2] = m02;

    m[3] = m03;
    m[4] = m04;
    m[5] = m05;

    m[6] = m06;
    m[7] = m07;
    m[8] = m08;

    for (int i = 0; i < 9; i++) {
        tm[0] = 0.0f;
    }
}

Mat3::Mat3(Vec3 v1, Vec3 v2, Vec3 v3) {
    m[0] = v1[0];
    m[1] = v1[1];
    m[2] = v1[2];

    m[3] = v2[0];
    m[4] = v2[1];
    m[5] = v2[2];

    m[6] = v3[0];
    m[7] = v3[1];
    m[8] = v3[2];

    for (int i = 0; i < 16; i++) {
        tm[0] = m[i];
    }
}

Mat3& Mat3::identity() {
    for (int i = 0; i < 9; i++) {
        m[i] = 0.0f;
        tm[i] = 0.0f;
    }
    m[0] = m[4] = m[8] = 1.0f;
    tm[0] = tm[4] = tm[8] = 1.0f;

    return *this;
}


Mat3& Mat3::transpose() {
    std::swap(m[1], m[3]);
    std::swap(m[2], m[6]);
    std::swap(m[5], m[7]);

    return *this;
}

Mat3& Mat3::invert() {
    float det, detInv;
    float tmp[9];

    tmp[0] = m[4] * m[8] - m[5] * m[7];
    tmp[1] = m[7] * m[2] - m[8] * m[1];
    tmp[2] = m[1] * m[5] - m[2] * m[4];
    tmp[3] = m[5] * m[6] - m[3] * m[8];
    tmp[4] = m[0] * m[8] - m[2] * m[6];
    tmp[5] = m[2] * m[3] - m[0] * m[5];
    tmp[6] = m[3] * m[7] - m[4] * m[6];
    tmp[7] = m[6] * m[1] - m[7] * m[0];
    tmp[8] = m[0] * m[4] - m[1] * m[3];

    // check if determinant is 0
    det = m[0] * tmp[0] + m[1] * tmp[3] + m[2] * tmp[6];
    if (fabs(det) <= EPSILON) {
        return identity();  // cannot invert
    }

    detInv = 1.0f / det;

    // divide by the determinant
    m[0] = detInv * tmp[0];
    m[1] = detInv * tmp[1];
    m[2] = detInv * tmp[2];
    m[3] = detInv * tmp[3];
    m[4] = detInv * tmp[4];
    m[5] = detInv * tmp[5];
    m[6] = detInv * tmp[6];
    m[7] = detInv * tmp[7];
    m[8] = detInv * tmp[8];

    return *this;
}


Mat3 Mat3::operator+(const Mat3& rhs) const {
    return Mat3(m[0] + rhs[0], m[1] + rhs[1], m[2] + rhs[2],
        m[3] + rhs[3], m[4] + rhs[4], m[5] + rhs[5],
        m[6] + rhs[6], m[7] + rhs[7], m[8] + rhs[8]);
}



Mat3 Mat3::operator-(const Mat3& rhs) const {
    return Mat3(m[0] - rhs[0], m[1] - rhs[1], m[2] - rhs[2],
        m[3] - rhs[3], m[4] - rhs[4], m[5] - rhs[5],
        m[6] - rhs[6], m[7] - rhs[7], m[8] - rhs[8]);
}

Mat3& Mat3::operator+=(const Mat3& rhs) {
    m[0] += rhs[0];  m[1] += rhs[1];  m[2] += rhs[2];
    m[3] += rhs[3];  m[4] += rhs[4];  m[5] += rhs[5];
    m[6] += rhs[6];  m[7] += rhs[7];  m[8] += rhs[8];

    return *this;
}


Mat3& Mat3::operator-=(const Mat3& rhs) {
    m[0] -= rhs[0];  m[1] -= rhs[1];  m[2] -= rhs[2];
    m[3] -= rhs[3];  m[4] -= rhs[4];  m[5] -= rhs[5];
    m[6] -= rhs[6];  m[7] -= rhs[7];  m[8] -= rhs[8];

    return *this;
}

Vec3 Mat3::operator*(const Vec3& rhs) const {
    return Vec3(m[0] * rhs.x + m[3] * rhs.y + m[6] * rhs.z,
        m[1] * rhs.x + m[4] * rhs.y + m[7] * rhs.z,
        m[2] * rhs.x + m[5] * rhs.y + m[8] * rhs.z);
}

Mat3 Mat3::operator*(const Mat3& rhs) const {
    return Mat3(m[0] * rhs[0] + m[3] * rhs[1] + m[6] * rhs[2],
                m[1] * rhs[0] + m[4] * rhs[1] + m[7] * rhs[2],
                m[2] * rhs[0] + m[5] * rhs[1] + m[8] * rhs[2],
                m[0] * rhs[3] + m[3] * rhs[4] + m[6] * rhs[5],
                m[1] * rhs[3] + m[4] * rhs[4] + m[7] * rhs[5],
                m[2] * rhs[3] + m[5] * rhs[4] + m[8] * rhs[5],
                m[0] * rhs[6] + m[3] * rhs[7] + m[6] * rhs[8],
                m[1] * rhs[6] + m[4] * rhs[7] + m[7] * rhs[8],
                m[2] * rhs[6] + m[5] * rhs[7] + m[8] * rhs[8]);
}

Mat3& Mat3::operator*=(const Mat3& rhs) {
    *this = *this * rhs;
    return *this;
}

float Mat3::operator[](int index) const {
    return m[index];
}

float& Mat3::operator[](int index) {
    return m[index];
}

Mat3 operator-(const Mat3& rhs) {
    return Mat3(-rhs[0], -rhs[1], -rhs[2], -rhs[3], -rhs[4], -rhs[5], -rhs[6],
        -rhs[7], -rhs[8]);
}

Mat3 operator*(float s, const Mat3& rhs) {
    return Mat3(s * rhs[0], s * rhs[1], s * rhs[2], 
                s * rhs[3], s * rhs[4], s * rhs[5], 
                s * rhs[6], s * rhs[7], s * rhs[8]);
}

std::ostream& operator<<(std::ostream& os, const Mat3& m) {
    os << std::fixed << std::setprecision(5);
    os << "[" << std::setw(10) << m[0] << " " << std::setw(10) << m[3] << " " << std::setw(10) << m[6] << "]\n"
        << "[" << std::setw(10) << m[1] << " " << std::setw(10) << m[4] << " " << std::setw(10) << m[7] << "]\n"
        << "[" << std::setw(10) << m[2] << " " << std::setw(10) << m[5] << " " << std::setw(10) << m[8] << "]\n";
    os << std::resetiosflags(std::ios_base::fixed | std::ios_base::floatfield);
    return os;
}



//
// Mat4
//
Mat4::Mat4() {
    // initially identity matrix
    identity();
}

Mat4::Mat4(float m00, float m01, float m02, float m03, 
           float m04, float m05, float m06, float m07, 
           float m08, float m09, float m10, float m11,
           float m12, float m13, float m14, float m15) {
    m[0] = m00;
    m[1] = m01;
    m[2] = m02;
    m[3] = m03;

    m[4] = m04;
    m[5] = m05;
    m[6] = m06;
    m[7] = m07;

    m[8] = m08;
    m[9] = m09;
    m[10] = m10;
    m[11] = m11;

    m[12] = m12;
    m[13] = m13;
    m[14] = m14;
    m[15] = m15;

    for (int i = 0; i < 16; i++) {
        tm[0] = m[i];
    }
}

Mat4::Mat4(Vec4 v1, Vec4 v2, Vec4 v3, Vec4 v4) {
    m[0] = v1[0];
    m[1] = v1[1];
    m[2] = v1[2];
    m[3] = v1[3];

    m[4] = v2[0];
    m[5] = v2[1];
    m[6] = v2[2];
    m[7] = v2[3];

    m[8] = v3[0];
    m[9] = v3[1];
    m[10] = v3[2];
    m[11] = v3[3];

    m[12] = v4[0];
    m[13] = v4[1];
    m[14] = v4[2];
    m[15] = v4[3];

    for (int i = 0; i < 16; i++) {
        tm[0] = 0.0f;
    }
}

Mat4& Mat4::identity() {
    for (int i = 0; i < 15; i++) {
        m[i] = 0.0f;
        tm[i] = 0.0f;
    }
    m[0] = m[5] = m[10] = m[15] = 1.0f;
    tm[0] = tm[5] = tm[10] = tm[15] = 1.0f;

    return *this;
}

Mat4& Mat4::transpose() {
    std::swap(m[1], m[4]);
    std::swap(m[2], m[8]);
    std::swap(m[3], m[12]);
    std::swap(m[6], m[9]);
    std::swap(m[7], m[13]);
    std::swap(m[11], m[14]);

    return *this;
}

Mat4& Mat4::invert() {
    Mat3 r(m[0], m[1], m[2], m[4], m[5], m[6], m[8], m[9], m[10]);
    
    r.invert();

    m[0] = r[0];  m[1] = r[1];  m[2] = r[2];
    m[4] = r[3];  m[5] = r[4];  m[6] = r[5];
    m[8] = r[6];  m[9] = r[7];  m[10] = r[8];

    // -R^-1 * T
    float x = m[12];
    float y = m[13];
    float z = m[14];

    m[12] = -(r[0] * x + r[3] * y + r[6] * z);
    m[13] = -(r[1] * x + r[4] * y + r[7] * z);
    m[14] = -(r[2] * x + r[5] * y + r[8] * z);

    // last row should be unchanged (0,0,0,1)
    //m[3] = m[7] = m[11] = 0.0f;
    //m[15] = 1.0f;

    return *this;
}


Mat4 Mat4::operator+(Mat4& rhs) {
    return Mat4(m[0] + rhs[0], m[1] + rhs[1], m[2] + rhs[2], m[3] + rhs[3],
        m[4] + rhs[4], m[5] + rhs[5], m[6] + rhs[6], m[7] + rhs[7],
        m[8] + rhs[8], m[9] + rhs[9], m[10] + rhs[10], m[11] + rhs[11],
        m[12] + rhs[12], m[13] + rhs[13], m[14] + rhs[14],
        m[15] + rhs[15]);
}

Mat4 Mat4::operator-(Mat4& rhs) {
    return Mat4(m[0] - rhs[0], m[1] - rhs[1], m[2] - rhs[2], m[3] - rhs[3],
        m[4] - rhs[4], m[5] - rhs[5], m[6] - rhs[6], m[7] - rhs[7],
        m[8] - rhs[8], m[9] - rhs[9], m[10] - rhs[10], m[11] - rhs[11],
        m[12] - rhs[12], m[13] - rhs[13], m[14] - rhs[14],
        m[15] - rhs[15]);
}

Vec4 Mat4::operator*(Vec4& rhs) {
    return Vec4(m[0] * rhs.x + m[4] * rhs.y + m[8] * rhs.z + m[12] * rhs.w,
        m[1] * rhs.x + m[5] * rhs.y + m[9] * rhs.z + m[13] * rhs.w,
        m[2] * rhs.x + m[6] * rhs.y + m[10] * rhs.z + m[14] * rhs.w,
        m[3] * rhs.x + m[7] * rhs.y + m[11] * rhs.z + m[15] * rhs.w);
}


float Mat4::operator[](int index) const {
    return m[index];
}



float& Mat4::operator[](int index) {
    return m[index];
}

Mat4& Mat4::translate(float x, float y, float z) {
    m[0] += m[3] * x;
    m[4] += m[7] * x;
    m[8] += m[11] * x;
    m[12] += m[15] * x;
    m[1] += m[3] * y;
    m[5] += m[7] * y;
    m[9] += m[11] * y;
    m[13] += m[15] * y;
    m[2] += m[3] * z;
    m[6] += m[7] * z;
    m[10] += m[11] * z;
    m[14] += m[15] * z;

    return *this;
}

Mat4& Mat4::scale(float s) { return scale(s, s, s); }

Mat4& Mat4::scale(float x, float y, float z) {
    m[0] *= x;
    m[4] *= x;
    m[8] *= x;
    m[12] *= x;

    m[1] *= y;
    m[5] *= y;
    m[9] *= y;
    m[13] *= y;

    m[2] *= z;
    m[6] *= z;
    m[10] *= z;
    m[14] *= z;

    return *this;
}

Mat4& Mat4::rotateX(float angle) {
    float c = cosf(angle * PI / 180.0f);
    float s = sinf(angle * PI / 180.0f);
    float m1 = m[1], m2 = m[2], m5 = m[5], m6 = m[6], m9 = m[9], m10 = m[10],
        m13 = m[13], m14 = m[14];

    m[1] = m1 * c + m2 * -s;
    m[2] = m1 * s + m2 * c;
    m[5] = m5 * c + m6 * -s;
    m[6] = m5 * s + m6 * c;
    m[9] = m9 * c + m10 * -s;
    m[10] = m9 * s + m10 * c;
    m[13] = m13 * c + m14 * -s;
    m[14] = m13 * s + m14 * c;

    return *this;
}

Mat4& Mat4::rotateY(float angle) {
    float c = cosf(angle * PI / 180.0f);
    float s = sinf(angle * PI / 180.0f);
    float m0 = m[0], m2 = m[2], m4 = m[4], m6 = m[6], m8 = m[8], m10 = m[10],
        m12 = m[12], m14 = m[14];

    m[0] = m0 * c + m2 * s;
    m[2] = m0 * -s + m2 * c;
    m[4] = m4 * c + m6 * s;
    m[6] = m4 * -s + m6 * c;
    m[8] = m8 * c + m10 * s;
    m[10] = m8 * -s + m10 * c;
    m[12] = m12 * c + m14 * s;
    m[14] = m12 * -s + m14 * c;

    return *this;
}

Mat4& Mat4::rotateZ(float angle) {
    float c = cosf(angle * PI / 180.0f);
    float s = sinf(angle * PI / 180.0f);

    float m0 = m[0], m1 = m[1], m4 = m[4], m5 = m[5], m8 = m[8], m9 = m[9],
        m12 = m[12], m13 = m[13];

    m[0] = m0 * c + m1 * -s;
    m[1] = m0 * s + m1 * c;
    m[4] = m4 * c + m5 * -s;
    m[5] = m4 * s + m5 * c;
    m[8] = m8 * c + m9 * -s;
    m[9] = m8 * s + m9 * c;
    m[12] = m12 * c + m13 * -s;
    m[13] = m12 * s + m13 * c;

    return *this;
}

std::ostream& operator<<(std::ostream& os, const Mat4& m) {
    os << std::fixed << std::setprecision(5);
    os << "[" << std::setw(10) << m[0] << " " << std::setw(10) << m[4] << " " << std::setw(10) << m[8] << " " << std::setw(10) << m[12] << "]\n"
        << "[" << std::setw(10) << m[1] << " " << std::setw(10) << m[5] << " " << std::setw(10) << m[9] << " " << std::setw(10) << m[13] << "]\n"
        << "[" << std::setw(10) << m[2] << " " << std::setw(10) << m[6] << " " << std::setw(10) << m[10] << " " << std::setw(10) << m[14] << "]\n"
        << "[" << std::setw(10) << m[3] << " " << std::setw(10) << m[7] << " " << std::setw(10) << m[11] << " " << std::setw(10) << m[15] << "]\n";
    os << std::resetiosflags(std::ios_base::fixed | std::ios_base::floatfield);
    return os;
}


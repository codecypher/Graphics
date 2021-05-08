/*
 * LinearAlgebra.cpp: Test xtensor setup
 */
#include "framework.h"
#include "CTensor.h"


CTensor::CTensor() {
}

 /**
  * Linear Algebra In C++ With XTensor is just Like Numpy
  * Towards Data Science
  */
int CTensor::hello_xtensor() {
    // First example
    xt::xarray<double> arr1
    { {1.0, 2.0, 3.0},
     {2.0, 5.0, 7.0},
     {2.0, 5.0, 7.0} };

    xt::xarray<double> arr2
    { 5.0, 6.0, 7.0 };

    // sum of second row of 2-dimensional array and 1-dimensional array.
    xt::xarray<double> sum = xt::view(arr1, 1) + arr2;

    std::cout << sum << std::endl;

    //
    // Second example: reshape
    //
    xt::xarray<int> arr
    { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    arr.reshape({ 3, 3 });

    std::cout << arr << std::endl;

    //
    // Third example: index access
    //
    xt::xarray<double> arr3
    { {1.0, 2.0, 3.0},
     {2.0, 5.0, 7.0},
     {2.0, 5.0, 7.0} };

    std::cout << arr3(0, 0) << std::endl;

    xt::xarray<int> arr4
    { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    std::cout << arr4(0) << std::endl;

    //
    // Fourth example: broadcasting
    //
    xt::xarray<double> arr5
    { 1.0, 2.0, 3.0 };

    xt::xarray<unsigned int> arr6
    { 4, 5, 6, 7 };

    arr6.reshape({ 4, 1 });

    xt::xarray<double> res = xt::pow(arr5, arr6);

    std::cout << res << std::endl;

    return 0;
}

int CTensor::xtensor_tutorial() {
    // Define 2x3 array
    // Since it inherits from xarray and not xtensor,
    // the dimensions of the matrix will be mutable.
    xt::xarray<int>array
    ({ {500, 500, 300}, {500, 600, 800} });
    std::cout << array << std::endl;

    // We can reshape our new array
    array.reshape({ 3, 2 });

    // We can cast a new type into all of the dims of our array
    xt::cast<double>(array);

    // We can also index our arrays the same way we would with Numpy,
    // but parenthesis are used to call indexes rather than brackets.
    std::cout << array(0, 2) << std::endl;


    xt::xarray<int>array1
    ({ {500, 500, 300}, {500, 600, 800} });

    // Our second array
    xt::xarray<int>array2
    ({ {500, 500, 300}, {500, 600, 800} });

    // Reshape it to fit first array's dimensions
    array2.reshape({ 3, 2 });

    // Concatenate it to the first array
    auto concat = xt::concatenate(xtuple(array, array2));
    std::cout << concat << std::endl;

    // We have access to linear algebraic operations such as dot,
    // but we need to access the linalg name-space.
    auto x = xt::linalg::dot(array1, array2);
    std::cout << x << std::endl;

    return 0;
}

int CTensor::la_review() {
    xt::xarray<int>u
        ({ {2}, {-5}, {-1} });

    xt::xarray<int>v
        ({ {3}, {2}, {-3} });

    // find the dot product
    auto x = xt::linalg::dot(xt::transpose(u), v);
    std::cout << x << std::endl;

    // add two matrices
    xt::xarray<int>A
    ({ {4, 0, 5}, {-1, 3, 2} });
    xt::xarray<int>B
    ({ {1, 1, 1}, {3, 5, 7} });

    std::cout << A + B << std::endl;

    // multiply by scalar
    std::cout << 2 * B << std::endl;

    // multiply two matrices
    xt::xarray<int>C
    ({ {2, 3}, {1, -5} });
    xt::xarray<int>D
    ({ {4, 3, 6}, {1, -2, 3} });

    auto res1 = xt::linalg::dot(C, D);

    std::cout << res1 << std::endl;

    // describe the identity matrix
    auto I = xt::eye<int>(3);

    std::cout << I << std::endl;

    // find the transpose of a matrix
    std::cout << xt::transpose(C) << std::endl;

    // find the determinant of a matrix
    xt::xarray<double>a
    ({ {1, 5, 0}, {2, 4, -1}, {0, -2, 0} });

    auto d = xt::linalg::det(a);

    std::cout << d << std::endl;

    // find the inverse of a matrix
    xt::xarray<double>b
    ({ {2, 5}, {-3, -7} });

    auto ainv = xt::linalg::inv(b);

    std::cout << ainv << std::endl;

    return 0;
}


int CTensor::main(int argc, char** argv) {
    std::ios::sync_with_stdio();  // notify compiler that both types of I/O will be used

    std::cout << "Hello, Jeff!" << std::endl;

    //hello_xtensor();
    //xtensor_tutorial();
    la_review();

    system("pause");

    return 0;
}



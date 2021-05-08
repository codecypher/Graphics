#include "framework.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "glm/ext.hpp"

#include "hello_glm.h"

void hello_glm() {
	// translating a vector of (1,0,0) by (1,1,0) 
	glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
	glm::mat4 trans = glm::mat4(1.0f);
	trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));
	vec = trans * vec;
	std::cout << vec.x << vec.y << vec.z << std::endl;

	// scale and rotate the container object
	// GLM expects its angles in radians so we convert the degrees to radians using glm::radians
	// The axis that we rotate around should be a unit vector, so be sure to 
	// normalize the vector first if you are not rotating around the X, Y, or Z axis.
	//glm::mat4 trans = glm::mat4(1.0f);
	trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));	// rotate the container 90 degrees around the Z-axis
	trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));						// scale the container by 0.5 on each axis
}


// LearnOpenGL
// OpenGL-Tutorial
// Matrices are in column-major order (column vectors)
void la_review() {
	glm::vec3 vec1(2.0f, -5.0f, -1.0f);
	glm::vec3 vec2(3.0f, 2.0f, -3.0f);
	glm::vec3 vec(0.0f, 0.0f, 0.0f);

	//vec = vec1 * vec2;
	//std::cout << "( " << vec.x << ", " << vec.y << ", " << vec.z << " )" << std::endl;

	// Find the dot product
	float x = glm::dot(vec1, vec2);
	std::cout << x << std::endl;

	// Add two matrices
	glm::mat2x3 A(glm::vec3(4.0f, 0.0f, 5.0f), glm::vec3(-1.0f, 3.0f, 2.0f));
	glm::mat2x3 B(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(-3.0f, 5.0f, 7.0f));
	std::cout << glm::to_string(A + B) << std::endl;

	// Multiply by scalar
	std::cout << glm::to_string(2 * B) << std::endl;

	// Multiply two matrices
	glm::mat2 D(glm::vec2(2.0f, 3.0f), glm::vec2(1.0f, -5.0f));
	glm::mat2 E(glm::vec2(4.0f, 3.0f), glm::vec2(1.0f, -2.0f));
	std::cout << glm::to_string(D * E) << std::endl;
	std::cout << glm::to_string(A * D) << std::endl;

	// Describe the identity matrix
	glm::mat3 identity = glm::mat3(1.0f);
	std::cout << glm::to_string(identity) << std::endl;

	// Find the transpose of a matrix
	//glm::mat3 T = A
	std::cout << glm::to_string(glm::transpose(A)) << std::endl;

	// Find the determinant of a matrix
	std::cout << glm::determinant(D) << std::endl;

	// Find the inverse of a matrix
	std::cout << glm::to_string(glm::inverse(D)) << std::endl;
}

void la_scratch() {
	// Geeks Example of Window Transform
	glm::mat3 M = glm::mat3(glm::vec3(0.5f, 0.0f, 0.0f),
		glm::vec3(0.0f, 0.5f, 0.0f),
		glm::vec3(20.0f, 20.0f, 1.0f));
	glm::vec3 mv = M * glm::vec3(30.0f, 80.0f, 1.0f);
	std::cout << glm::to_string(mv) << std::endl;		// [35, 60, 1]

	// Translation example
	glm::mat3 T = glm::mat3(glm::vec3(1.0f, 0.0f, 1.0f),
		glm::vec3(0.0f, 1.0f, 2.0f),
		glm::vec3(0.0f, 0.0f, 1.0f));
	glm::vec3 tx = T * glm::vec3(4.0f, 5.0, 6.0);
	std::cout << glm::to_string(tx) << std::endl;		// [4, 5, 20]

	float vmin[] = { 0.0f, 0.0f };
	float vmax[] = { float(640 - 1),
					 float(480 - 1) };
	float wmin[] = { 0.0f, 0.0f };
	float wmax[] = { 10.0f, 10.0f };

	float a[2] = { 0.0f, 0.0f };
	float b[2] = { 0.0f, 0.0f };
	a[0] = (vmax[0] - vmin[0]) / (wmax[0] - wmin[0]);
	a[1] = (vmax[1] - vmin[1]) / (wmax[1] - wmin[1]);
	b[0] = (vmin[0] * wmax[0] - vmax[0] * wmin[0]) / (wmax[0] - wmin[0]);
	b[1] = (vmin[1] * wmax[1] - vmax[1] * wmin[1]) / (wmax[1] - wmin[1]);

	glm::mat3 m = glm::mat3(1.0f);  // identity matrix
	m = glm::mat3(glm::vec3(a[0], 0.0f, 0.0f),
		glm::vec3(0.0f, a[1], 0.0f),
		glm::vec3(b[0], b[1], 1.0f));
	mv = m* glm::vec3(10.0, 10.0, 1.0);
	std::cout << glm::to_string(mv) << std::endl;
}

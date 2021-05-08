#version 330 core

// declare input vertex attributes
layout (location = 0) in vec3 aPos;

void main() {
  // assign the position data to the predefined variable
  gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}

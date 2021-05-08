#version 330 core
layout (location = 0) in vec3 vPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 MVP;

void main() {
	//gl_Position = projection * view * model * vec4(vPos, 1.0);
	//gl_Position = vec4(vPos.x, vPos.y, vPos.z, 1.0);
	//gl_Position = view * model * vec4(vPos, 1.0);
	gl_Position = MVP * vec4(vPos, 1.0);
}
#version 460 core

layout (location = 0) in vec2 position;
layout (location = 1) in vec3 colorIN;

out vec3 color;
// uniform mat4 model;

void main() {
	gl_Position = /*model **/ vec4(position, 1.0, 1.0);
	color = colorIN;
}
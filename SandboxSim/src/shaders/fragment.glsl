#version 460 core

in vec3 color;

out vec4 fragColor;

void main() {
	// fragColor = vec4(1.0, 0.77, 0.34, 1.0);
	fragColor = vec4(color, 1.0);
}
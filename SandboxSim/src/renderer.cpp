#include <glad/glad.h>
#include "../headers/renderer.h"

void Renderer::clear() {
	glClearColor(0.12f, 0.14f, 0.17f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}


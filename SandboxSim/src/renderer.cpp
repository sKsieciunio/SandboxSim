#include <glad/glad.h>
#include "../headers/renderer.h"

void Renderer::clear() {
	glClearColor(0.22f, 0.24f, 0.27f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}


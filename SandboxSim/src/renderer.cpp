#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "shader.h"
#include "../headers/renderer.h"

void Renderer::renderBoard(Shader& shader, float* indices, int size) {
	shader.use();
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * size, indices, GL_STATIC_DRAW);
	glDrawArrays(GL_TRIANGLES, 0, size);
}

void Renderer::renderRecGrid(Shader& shader, int posX, int posY) {
	shader.use();
	glm::mat4 model = glm::identity<glm::mat4>();
	model = glm::scale(model, glm::vec3(scale));
	model = glm::translate(model, glm::vec3(1.0f, -1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(
		-static_cast<float>(gridSize) + 2 * posX,
		static_cast<float>(gridSize) - 2 * posY,
		0.0f
	));
	shader.setMat4("model", model);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Renderer::clear() {
	glClearColor(0.12f, 0.14f, 0.17f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}
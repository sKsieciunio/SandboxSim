#pragma once
#include <glad/glad.h>
#include "shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

extern const float scale;
extern const int gridSize;

namespace Renderer
{

	void renderRecGrid(Shader& shader, int posX, int posY) {
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


	void clear() {
		glClearColor(0.12f, 0.14f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}
}
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "headers/shader.h"
#include "headers/renderer.h"
#include "headers/board.h"
#include "headers/grain.h"

void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

const unsigned int SCREEN_WIDTH{ 800 };
const unsigned int SCREEN_HEIGHT{ 800 };
const float scale{ 0.005f };
const int gridSize{ static_cast<int>(1 / scale) };

const float recVertices[] = {
	 1.0f,  1.0f,
	-1.0f,  1.0f,
	-1.0f, -1.0f,
	-1.0f, -1.0f,
	 1.0f, -1.0f,
	 1.0f,  1.0f
};

Board board{ gridSize };

int main(void) {
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Sandbox", NULL, NULL);

	if (!window) glfwTerminate();

	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
	//glfwSetMouseButtonCallback(window, mouseButtonCallback);

	Shader shader(".\\src\\shaders\\vertex.glsl", ".\\src\\shaders\\fragment.glsl");

	unsigned int VBO{}, VAO{};
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(recVertices), recVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	board.addGrain(100, 100);

	while (!glfwWindowShouldClose(window)) {
		processInput(window);

		Renderer::clear();

		board.calculatePhysics();

		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT)) {
			double xpos{}, ypos{};
			glfwGetCursorPos(window, &xpos, &ypos);
			if (xpos >= 0 && xpos < SCREEN_WIDTH && ypos >= 0 && ypos < SCREEN_HEIGHT) {
				int x{ static_cast<int>(xpos / (SCREEN_WIDTH / gridSize)) };
				int y{ static_cast<int>(ypos / (SCREEN_HEIGHT / gridSize)) };
				//std::cout << x << ',' << y << std::endl;
				board.addGrain(x, y);
			}
		}

		board.render(shader);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		double xpos{}, ypos{};
		glfwGetCursorPos(window, &xpos, &ypos);
		std::cout << xpos << ',' << ypos << std::endl;
	}
}
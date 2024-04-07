#include <iostream>
#include <iomanip>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <ctime>
#include <cstdlib>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "headers/shader.h"
#include "headers/renderer.h"
#include "headers/board.h"

void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

const unsigned int SCREEN_WIDTH{ 800 };
const unsigned int SCREEN_HEIGHT{ 800 };
const float scale{ 0.005f };
const int gridSize{ static_cast<int>(1 / scale) };
const float physicsRate{ 60.0f }; // Physics engine refresh rate [Hz]
const float physicsTime{ 1 / physicsRate };

Board board{ gridSize };
float deltaTime{ 0.0f };
float lastFrame{ 0.0f };
Grain::Type currentGrainType = Grain::Type::SAND;

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
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)2);
	glEnableVertexAttribArray(1); 

	board.addGrain(100, 100, currentGrainType);
	srand(time(nullptr));

	while (!glfwWindowShouldClose(window)) {
		float currentFrame{ static_cast<float>(glfwGetTime()) };
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		std::cout << "FPS: " << std::setfill(' ') << std::setw(6) << std::fixed << std::setprecision(2) << 1 / deltaTime << " / " << deltaTime * 100 << " ms";

		processInput(window);

		Renderer::clear();

		double time1{ glfwGetTime() };
		// PHYSICS HERE
		static float timeWhenToCalPhy = 0.0f;
		if (glfwGetTime() > timeWhenToCalPhy) {
			board.calculatePhysics();
			timeWhenToCalPhy += physicsTime;
		}
		std::cout << "\t\tPhysics Enigne Time: " << (glfwGetTime() - time1) * 100 << " ms";

		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT)) {
			double xpos{}, ypos{};
			glfwGetCursorPos(window, &xpos, &ypos);
			if (xpos >= 0 && xpos < SCREEN_WIDTH && ypos >= 0 && ypos < SCREEN_HEIGHT) {
				int x{ static_cast<int>(xpos / (SCREEN_WIDTH / gridSize)) };
				int y{ static_cast<int>(ypos / (SCREEN_HEIGHT / gridSize)) };
				board.addGrain(x, y, currentGrainType);
			}
		}

		double time2{ glfwGetTime() };
		board.render2(shader); // RENDERING HERE
		std::cout << "\t\tRender Time: " << (glfwGetTime() - time2) * 100 << " ms" << std::endl;

		/*
		for (int i = 0; i < board.boardSize; ++i) {
			board.addGrain(i, i%2 + 1);
		}
		*/

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
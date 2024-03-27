#include "../headers/app.h"
#include <iostream>

App::App(unsigned int width, unsigned int height, const char* title) :
  screenWidth{ width },
  screenHeight{ height },
  windowTitle{ title }
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(width, height, title, NULL, NULL);

	if (!window) {
		glfwTerminate();
	}

	glfwMakeContextCurrent(window);

	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
}

App::~App() {
	glfwTerminate();
}

void App::gameLoop() {
	while (!glfwWindowShouldClose(window)) {
		glClearColor(1.0f, 0.5f, 0.31f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);
		glfwPollEvents();		
	}
}
#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class App {
private:
	unsigned int screenWidth;
	unsigned int screenHeight;
	const char* windowTitle;
	GLFWwindow* window;
public:
	App(unsigned int width = 800, unsigned int height = 800, const char* title = "OpenGL");
	~App();
	void gameLoop();
private:
	void processInput();
};

void framebufferSizeCallback(GLFWwindow* window, int width, int height);
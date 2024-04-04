#pragma once
#include "renderer.h"

class Shader;

class Grain {
	int posX;
	int posY;
public:
	Grain(int posX, int posY) : posX{ posX }, posY{ posY } {}

	void render(Shader& shader) {
		Renderer::renderRecGrid(shader, posX, posY);
	}

	void updatePos(int x, int y) {
		posX = x;
		posY = y;
	}
};
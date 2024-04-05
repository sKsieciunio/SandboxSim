#pragma once
#include "renderer.h"

class Shader;

class Grain {
public:
	int posX;
	int posY;

	enum class Type {SAND, WATER};
	Type type;

	Grain(int posX, int posY, Type type) : posX{ posX }, posY{ posY }, type{ type } {}

	void render(Shader& shader) {
		Renderer::renderRecGrid(shader, posX, posY);
	}

	void updatePos(int x, int y) {
		posX = x;
		posY = y;
	}
};
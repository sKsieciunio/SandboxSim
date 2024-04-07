#pragma once
#include "renderer.h"
#include "functions.h"

class Shader;

class Grain {
public:
	int posX;
	int posY;

	enum class Type {SAND, WATER};
	Type type;

	Grain(int posX, int posY, Type type) : posX{ posX }, posY{ posY }, type{ type } {}

	void render2(Shader& shader) {
		float indices[30];

		indices[0] = mappingFunc(posX + 1);
		indices[1] = -mappingFunc(posY);
		indices[2] = 0.9f;
		indices[3] = 0.77f;
		indices[4] = 0.34f;

		indices[5] = mappingFunc(posX);
		indices[6] = -mappingFunc(posY);
		indices[7] = 0.9f;
		indices[8] = 0.77f;
		indices[9] = 0.34f;

		indices[10] = mappingFunc(posX);
		indices[11] = -mappingFunc(posY + 1);
		indices[12] = 0.9f;
		indices[13] = 0.77f;
		indices[14] = 0.34f;

		indices[15] = mappingFunc(posX);
		indices[16] = -mappingFunc(posY + 1);
		indices[17] = 0.9f;
		indices[18] = 0.77f;
		indices[19] = 0.34f;

		indices[20] = mappingFunc(posX + 1);
		indices[21] = -mappingFunc(posY + 1);
		indices[22] = 0.9f;
		indices[23] = 0.77f;
		indices[24] = 0.34f;

		indices[25] = mappingFunc(posX + 1);
		indices[26] = -mappingFunc(posY);
		indices[27] = 0.9f;
		indices[28] = 0.77f;
		indices[29] = 0.34f;

		Renderer::renderIndices(shader, indices, 30);
	}

	void render(Shader& shader) {
		Renderer::renderRecGrid(shader, posX, posY);
	}

	void updatePos(int x, int y) {
		posX = x;
		posY = y;
	}
};
#pragma once
#include "grain.h"

class Shader;

class Board {

public:
	Grain*** board;
	int boardSize;

	Board(int size);
	~Board();

	void render(Shader& shader);
	void renderNew(Shader& shader);
	void calculatePhysics();
	void addGrain(int x, int y, Grain::Type type);
};
#pragma once

class Grain;
class Shader;

class Board {

public:
	Grain*** board;
	int boardSize;

	Board(int size);
	~Board();

	void render(Shader& shader);
	void calculatePhysics();
	void addGrain(int x, int y);
};
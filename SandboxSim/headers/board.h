#pragma once

class Grain;

class Board {
	Grain*** board;
	int boardSize;
public:
	Board(int size);
	~Board();

	void render();
};
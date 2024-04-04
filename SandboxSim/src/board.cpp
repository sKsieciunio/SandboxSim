#include "../headers/board.h"
#include "../headers/grain.h"
#include <new>

Board::Board(int size) 
	: board{}, boardSize{ size } {
	board = new (std::nothrow) Grain**[size];
	if (!board) return;

	for (int i = 0; i < size; ++i) {
		board[i] = new (std::nothrow) Grain*[size];
		if (!board[i]) return;

		for (int j = 0; j < size; ++j) {
			board[i][j] = nullptr;
		}
	}
}

Board::~Board() {
	for (int i = 0; i < boardSize; ++i) {
		for (int j = 0; j < boardSize; ++j) {
			delete board[i][j];
		}
		delete[] board[i];
	}
	delete[] board;
}

void Board::render(Shader& shader) {
	for (int i = 0; i < boardSize; ++i) 
		for (int j = 0; j < boardSize; ++j) 
			if (board[i][j] != nullptr) 
				board[i][j]->render(shader);
}

void Board::calculatePhysics() {
	// we dont iterate over 39th row cuz it is not supposed to change
	for (int y = boardSize - 2; y >= 0; --y) {
		for (int x = 0; x < boardSize; ++x) {
			if (board[x][y] == nullptr) continue;
			if (board[x][y + 1] == nullptr) {
				board[x][y + 1] = board[x][y];
				board[x][y] = nullptr;
				board[x][y + 1]->updatePos(x, y + 1);
			}
		}
	}
}

void Board::addGrain(int x, int y) {
	if (board[x][y] == nullptr) {
		board[x][y] = new (std::nothrow) Grain{ x, y };
		if (board[x][y] == nullptr) return;
	}
}

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
	for (int i = 0; i < boardSize; ++i) {
		for (int j = 0; j < boardSize; ++j) {
			if (board[i][j] != nullptr) {
				board[i][j]->render(shader);
			}
		}
	}
}

void Board::calculatePhysics() {

}

void Board::addGrain(int x, int y) {
	if (board[x][y] == nullptr) {
		board[x][y] = new (std::nothrow) Grain{ x, y };
		if (board[x][y] == nullptr) return;
	}
}

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

// Code written by chatgpt xd
static float mappingFunc(int value) {
	float minIn{ 0.0f }, maxIn{ 200.0f }, minOut{ -1.0f }, maxOut{ 1.0f };
	float fraction = static_cast<float>(value - minIn) / (maxIn - minIn);
	float mappedValue = minOut + fraction * (maxOut - minOut);
	return mappedValue;
}

void Board::renderNew(Shader& shader) {
	float* indices = new (std::nothrow) float[boardSize * boardSize * 12] {};
	if (indices == nullptr) return;

	for (int y = 0; y < boardSize; ++y) {
		for (int x = 0; x < boardSize; ++x) {
			if (board[x][y] == nullptr) continue;
			int arrayOffset = y * boardSize * 12 + x * 12;
			int Xpos = board[x][y]->posX;
			int Ypos = board[x][y]->posY;
			indices[arrayOffset + 0 ] =  mappingFunc(Xpos + 1);
			indices[arrayOffset + 1 ] = -mappingFunc(Ypos);
			indices[arrayOffset + 2 ] =  mappingFunc(Xpos);
			indices[arrayOffset + 3 ] = -mappingFunc(Ypos);
			indices[arrayOffset + 4 ] =  mappingFunc(Xpos);
			indices[arrayOffset + 5 ] = -mappingFunc(Ypos + 1);
			indices[arrayOffset + 6 ] =  mappingFunc(Xpos);
			indices[arrayOffset + 7 ] = -mappingFunc(Ypos + 1);
			indices[arrayOffset + 8 ] =  mappingFunc(Xpos + 1);
			indices[arrayOffset + 9 ] = -mappingFunc(Ypos + 1);
			indices[arrayOffset + 11] = -mappingFunc(Ypos);
			indices[arrayOffset + 10] =  mappingFunc(Xpos + 1);
		}
	}

	Renderer::renderBoard(shader, indices, boardSize * boardSize * 12);

	delete[] indices;
}

void Board::render(Shader& shader) {
	for (int i = 0; i < boardSize; ++i) 
		for (int j = 0; j < boardSize; ++j) 
			if (board[i][j] != nullptr) 
				board[i][j]->render(shader);
}

void Board::calculatePhysics() {
	// we dont iterate over last row cuz it is not supposed to change
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

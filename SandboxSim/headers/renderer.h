#pragma once

extern const float scale;
extern const int gridSize;

class Shader;

namespace Renderer
{

void clear();
void renderRecGrid(Shader& shader, int posX, int posY);
void renderBoard(Shader& shader, float* indices, int size);
void renderIndices(Shader& shader, float* indices, int size);

}
#pragma once

extern const float scale;
extern const int gridSize;

class Shader;

namespace Renderer
{

void renderRecGrid(Shader& shader, int posX, int posY);
void clear();

}
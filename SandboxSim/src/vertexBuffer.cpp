#include <glad/glad.h>
#include "../headers/vertexBuffer.h"

VertexBuffer::VertexBuffer() 
	: ID{} {
	glGenBuffers(1, &ID);
}

VertexBuffer::VertexBuffer(const float data[])
	: ID{} {
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer() {
	glDeleteBuffers(1, &ID);
}
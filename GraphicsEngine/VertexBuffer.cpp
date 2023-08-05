#include "pch.h"
#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(GLuint size, const void* data): Buffer(size), data{data}
{
	glGenBuffers(1, &index);
	glBindBuffer(GL_ARRAY_BUFFER, index);
	glBufferData(GL_ARRAY_BUFFER, sizeof(char) * size, data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(sizeof(char) * size, &index);
}


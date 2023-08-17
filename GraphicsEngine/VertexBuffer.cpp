#include "pch.h"
#include "VertexBuffer.h"


VertexBuffer::VertexBuffer(GLuint size, const void* data) :size{size}
{
	if (size > 0) {
		glGenBuffers(1, &index);
		glBindBuffer(GL_ARRAY_BUFFER, index);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * size, data, GL_STATIC_DRAW);
	}
}

GLuint VertexBuffer::getIndex() const
{
	return index;
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(sizeof(Vertex) * size, &index);
}


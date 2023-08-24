#include "pch.h"
#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(GLuint size, const void* data) : size{size}
{
	if (size) {
		glGenBuffers(1, &index);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(unsigned int), data, GL_STATIC_DRAW);
	}
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(size, &index);
}

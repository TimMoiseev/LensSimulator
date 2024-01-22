#include "pch.h"
#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(GLuint size, const void* data) : size{size}
{
	if (size) {
		glGenBuffers(1, &index);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(unsigned int), data, GL_DYNAMIC_DRAW);
	}
}

void IndexBuffer::updateIndexBuffer(GLuint newSize, const void* newData)
{
	if (newSize > size) {
		glDeleteBuffers(1, &index);
		glGenBuffers(1, &index);
		glBindBuffer(GL_ARRAY_BUFFER, index);
		glBufferData(GL_ARRAY_BUFFER, sizeof(unsigned int) * newSize, newData, GL_DYNAMIC_DRAW);
	}
	else{
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(unsigned int) * newSize, newData);
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	size = newSize;
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &index);
}

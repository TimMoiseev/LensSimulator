#include "pch.h"
#include "VertexBuffer.h"


VertexBuffer::VertexBuffer(GLuint size, const void* data) :size{size}
{
	if (size > 0) {
		glGenBuffers(1, &index);
		glBindBuffer(GL_ARRAY_BUFFER, index);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * size, data, GL_DYNAMIC_DRAW);
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::updateVertexBuffer(GLuint newSize, const void* newData)
{
	if (newSize > size) {
		glDeleteBuffers(1, &index);
		glGenBuffers(1, &index);
		glBindBuffer(GL_ARRAY_BUFFER, index);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * newSize, newData, GL_DYNAMIC_DRAW);
	}
	else{
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vertex) * newSize, newData);
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	size = newSize;
}

GLuint VertexBuffer::getIndex() const
{
	return index;
}

GLuint VertexBuffer::getSize() const
{
	return size;
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &index);
}


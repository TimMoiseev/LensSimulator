#include "pch.h"
#include "VertexBuffer.h"
#include <GL/glew.h>
#include <vector>
#include "Vertex.h"

VertexBuffer::VertexBuffer(GLuint size, const void* data)
{
	if (size > 0) {
		glGenBuffers(1, &index);
		glBindBuffer(GL_ARRAY_BUFFER, index);
		glBufferData(GL_ARRAY_BUFFER, sizeof(char) * size, data, GL_STATIC_DRAW);
	}
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(sizeof(char) * size, &index);
}


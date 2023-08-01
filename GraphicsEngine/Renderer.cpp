#include "pch.h"
#include "Renderer.h"
#include "Vertex.h"

void Renderer::bindVertexBuffer(const VertexBuffer& buf)
{
	glBindBuffer(GL_ARRAY_BUFFER, buf.vertexBufferIndex);
}

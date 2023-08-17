#include "pch.h"
#include "Renderer.h"


void Renderer::draw(Scene* scene)
{

}

void Renderer::bindVertexBuffer(const VertexBuffer* buf)
{
	glBindBuffer(GL_ARRAY_BUFFER, buf->getIndex());
}

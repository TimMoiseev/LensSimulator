#include "pch.h"
#include "Renderer.h"



void Renderer::setCamera(Camera* cam)
{
	shaderSystem->bindUniformParameters("cameraMatrix", &cam->getCameraMatrix()[0][0]);
}

Renderer::Renderer(ShaderSystem* shaderSystem) : shaderSystem { shaderSystem }
{
	shaderSystem->shaderProgram->use();
}

void Renderer::draw(Primitive* primitive)
{
	
	shaderSystem->bindUniformParameters("objectMatrix", primitive->getObjectMatrix());
	primitive->bindArrayAttrib();
	
	/*bindIndexBuffer(primitive->IndicesView());*/
	glDrawElements(
		primitive->getGeometryType() == Scene::GeometryType::Triangles ? GL_TRIANGLES : GL_LINES,
		primitive->IndicesView()->getSize(),
		GL_UNSIGNED_INT,
		(void*)0
	);
}

void Renderer::draw(std::vector<Primitive*> primitives)
{
	for (auto scene : primitives) { draw(scene); };
}

//void Renderer::bindIndexBuffer(const IndexBuffer* buf)
//{
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buf->getIndex());
//
//}

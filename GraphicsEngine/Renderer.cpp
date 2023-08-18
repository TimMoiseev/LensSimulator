#include "pch.h"
#include "Renderer.h"


void Renderer::setCamera(Camera* cam)
{
	shaderSystem->bindUniformParameters("cameraMatrix", &cam->getCameraMatrix()[0][0]);
}

Renderer::Renderer(ShaderSystem* shaderSystem) : shaderSystem{shaderSystem}
{
	shaderSystem->shaderProgram->use();
}

void Renderer::draw(Scene* scene)
{
	
	shaderSystem->bindUniformParameters("objectMatrix", &scene->objectMatrix[0][0]);
	scene->bindArrayAttrib();
	
	bindIndexBuffer(scene->IndicesView());
	glDrawElements(
		GL_TRIANGLES,      // mode
		scene->IndicesView()->getSize(),    // count
		GL_UNSIGNED_INT,   // type
		(void*)0           // element array buffer offset
	);
}

void Renderer::draw(std::vector<Scene*> scenes)
{
	for (auto scene : scenes) { draw(scene); };
}

void Renderer::bindIndexBuffer(const IndexBuffer* buf)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buf->getIndex());

}

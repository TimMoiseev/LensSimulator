#pragma once
#include "VertexBuffer.h"
#include "Scene.h"
#include "ShaderSystem.h"
#include "Camera.h"
class Renderer
{
	ShaderSystem* shaderSystem;
public:
	void setCamera(Camera* cam);
	Renderer(ShaderSystem* shaderSystem);
	Renderer() = delete;
	void draw(Scene* scene);
	void draw(std::vector<Scene*> scenes);
	void bindIndexBuffer(const IndexBuffer* buf);
};


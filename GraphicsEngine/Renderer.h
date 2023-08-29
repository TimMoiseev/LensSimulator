#pragma once
#include "VertexBuffer.h"
#include "Scene.h"
#include "ShaderSystem.h"
#include "Camera.h"
#include "Primitive.h"
class Renderer
{
	ShaderSystem* shaderSystem;
public:
	void setCamera(Camera* cam);
	Renderer(ShaderSystem* shaderSystem);
	Renderer() = delete;
	void draw(Primitive* primitive);
	void draw(std::vector<Primitive*> primitives);
	void bindIndexBuffer(const IndexBuffer* buf);
};
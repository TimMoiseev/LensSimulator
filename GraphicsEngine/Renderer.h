#pragma once
#include "VertexBuffer.h"
#include "Scene.h"
class Renderer
{
public:
	void draw(Scene* sdcene);
	void bindVertexBuffer(const VertexBuffer* buf);
};


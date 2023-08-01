#pragma once
#include <vector>
#include "Vertex.h"
#include "Buffer.h"
#include "VertexBuffer.h"
class Scene
{
	std::vector<Vertex> vertices;
	VertexBuffer buff;
	VertexType type;
public:
	Scene(const std::vector<Vertex>& vertices, VertexType type);
	const VertexBuffer VerticesView();
};



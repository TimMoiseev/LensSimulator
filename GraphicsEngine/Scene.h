#pragma once
#include <vector>
#include "Vertex.h"
#include "Buffer.h"
#include "VertexBuffer.h"
#include "glm/glm.hpp"
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

class Scene
{
	std::vector<Vertex> vertices;
	VertexBuffer buff;
	VertexType type;
	
public:
	glm::mat4 objectMatrix = glm::mat4(1.0f); //objects translation and rotation
	Scene(const std::vector<Vertex>& vertices, VertexType type);
	void bindArrayAtrib();
	~Scene();
	const VertexBuffer VerticesView();
};



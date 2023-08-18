#pragma once
#include <vector>
#include "Vertex.h"
#include "VertexBuffer.h"
#include "glm/glm.hpp"
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include "IndexBuffer.h"

class Scene
{
protected:
	void createBuffer(std::vector<Vertex>* vertexArray, std::vector<GLuint>* indexArray);
private:
	VertexBuffer* buff = nullptr;
	IndexBuffer* indexBuffer = nullptr;
	VertexType type;
	
public:
	glm::mat4 objectMatrix = glm::mat4(1.0f); //objects translation and rotation
	Scene(VertexType type = Coordinate | Color);
	void bindArrayAttrib();
	virtual void update(float duration) = 0;
	~Scene();
	const IndexBuffer* IndicesView();
};



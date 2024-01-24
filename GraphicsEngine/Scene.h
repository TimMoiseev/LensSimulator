#pragma once
#include <vector>
#include "Vertex.h"
#include "VertexBuffer.h"
#include "glm/glm.hpp"
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include "IndexBuffer.h"

using vec3 = glm::vec3;
using mat4 = glm::mat4;

class Scene
{
public:
	
protected:
	void createBuffer(std::vector<Vertex>* vertexArray, std::vector<GLuint>* indexArray);
	void updateBufferData(std::vector<Vertex>* vertexArray, std::vector<GLuint>* indexArray);
	int geometryType = GL_TRIANGLES;
private:
	VertexBuffer* vertexBuffer = nullptr;
	IndexBuffer* indexBuffer = nullptr;
	VertexType type;
public:
	Scene(VertexType type = Coordinate | Color, int geometryType = GL_TRIANGLES);
	void bindArrayAttrib();
	
	virtual void update(float duration) {};
	int getGeometryType() { return geometryType; }
	~Scene();
	const IndexBuffer* IndicesView();
};



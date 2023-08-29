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
	enum GeometryType {
		Triangles = 3,
		Lines = 2
	};
protected:
	void createBuffer(std::vector<Vertex>* vertexArray, std::vector<GLuint>* indexArray);
	GeometryType geometryType = Lines;
private:
	VertexBuffer* buff = nullptr;
	IndexBuffer* indexBuffer = nullptr;
	VertexType type;
public:
	Scene(VertexType type = Coordinate | Color, GeometryType geometryType = Triangles);
	void bindArrayAttrib();
	virtual void update(float duration) = 0;
	GeometryType getGeometryType() { return geometryType; }
	~Scene();
	const IndexBuffer* IndicesView();
};



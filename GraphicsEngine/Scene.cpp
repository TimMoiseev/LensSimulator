#include "pch.h"
#include "Scene.h"

void Scene::createBuffer(std::vector<Vertex>* vertexArray, std::vector<GLuint>* indexArray)
{
	vertexBuffer = new VertexBuffer((GLuint)vertexArray->size(), vertexArray->data());
	indexBuffer = new IndexBuffer((GLuint)indexArray->size(), indexArray->data());
}

void Scene::updateBufferData(std::vector<Vertex>* vertexArray, std::vector<GLuint>* indexArray)
{
	vertexBuffer->updateVertexBuffer((GLuint)vertexArray->size(), vertexArray->data());
	indexBuffer->updateIndexBuffer((GLuint)indexArray->size(), indexArray->data());
}

Scene::Scene(VertexType type, int geometryType) : type{type}, geometryType{ geometryType }
{
	
}

void Scene::bindArrayAttrib()
{

	if (type & Coordinate) {
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer->getIndex());
		void* p0 = reinterpret_cast<void*>(offsetof(Vertex, vert));
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), p0);
	}
	if (type & Color) {
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer->getIndex());
		void* p1 = reinterpret_cast<void*>(offsetof(Vertex, color));
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), p1);
	}
	if (type & Normal) {
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer->getIndex());
		void* p2 = reinterpret_cast<void*>(offsetof(Vertex, normal));
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), p2);
	}
	if (indexBuffer != nullptr) {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer->getIndex());
	}
	
}

Scene::~Scene()
{
	delete vertexBuffer;
	delete indexBuffer;
}

const IndexBuffer* Scene::IndicesView()
{
	return indexBuffer;
}

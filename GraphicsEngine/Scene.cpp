#include "pch.h"
#include "Scene.h"

Scene::Scene(const std::vector<Vertex>& vertices, VertexType type) : vertices{vertices}, buff{vertices.size()*sizeof(Vertex),vertices.data()}, type{type}
{
	
}

void Scene::bindArrayAtrib()
{
	if (type & Coordinate) {
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, buff.getIndex());
		void* p0 = reinterpret_cast<void*>(offsetof(Vertex, vert));
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), p0);
	}
	if (type & Color) {
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, buff.getIndex());
		void* p1 = reinterpret_cast<void*>(offsetof(Vertex, color));
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), p1);
	}
	if (type & Normal) {
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, buff.getIndex());
		void* p2 = reinterpret_cast<void*>(offsetof(Vertex, normal));
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), p2);
	}
}

Scene::~Scene()
{
}

const VertexBuffer Scene::VerticesView()
{
	return buff;
}

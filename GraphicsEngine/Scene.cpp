#include "pch.h"
#include "Scene.h"

Scene::Scene(const std::vector<Vertex>& vertices, VertexType type) : vertices{vertices}, buff{vertices.size()*sizeof(Vertex),vertices.data()}, type{type}
{
	if (type & Coordinate) {
		glEnableVertexAttribArray(0);
		void* p0 = reinterpret_cast<void*>(offsetof(Vertex, vert));
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), p0);
	}
	if (type & Color) {
		glEnableVertexAttribArray(1);
		void* p1 = reinterpret_cast<void*>(offsetof(Vertex, color));
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), p1);
	}
	if (type & Normal) {
		glEnableVertexAttribArray(2);
		void* p2 = reinterpret_cast<void*>(offsetof(Vertex, normal));
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), p2);
	}
}

const VertexBuffer Scene::VerticesView()
{
	return buff;
}

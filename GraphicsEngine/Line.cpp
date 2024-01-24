#include "pch.h"
#include "Line.h"

Line::Line(glm::vec3 point1, glm::vec3 point2, glm::vec3 color) : 
	firstPoint{ point1 }, 
	secondPoint{ point2 },
	color{color} {
	geometryType = GL_LINES;
	createModel();
	createBuffer(vertices, indices);
}

void Line::update(float duration)
{
}

void Line::createModel() {
	vertices->push_back(Vertex({ firstPoint.x, firstPoint.y, firstPoint.z}, {color.r, color.g, color.b}));
	vertices->push_back(Vertex({ secondPoint.x, secondPoint.y, secondPoint.z }, { color.r, color.g, color.b }));
	indices->push_back(0);
	indices->push_back(1);
}
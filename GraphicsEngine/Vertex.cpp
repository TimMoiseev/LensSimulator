#include "pch.h"
#include "Vertex.h"

Vertex::Vertex(std::array<GLfloat, 3> vert, std::array<GLfloat, 3> color)
{
	this->vert = vert;
	this->color = color;
}

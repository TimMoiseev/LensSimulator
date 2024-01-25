#include "pch.h"
#include "Vertex.h"

Vertex::Vertex(std::array<GLfloat, 3> vert, std::array<GLfloat, 3> color, std::array<GLfloat, 3> normal)
{
	this->vert = vert;
	this->color = color;
	this->normal = normal;
}

Vertex::~Vertex()
{

}

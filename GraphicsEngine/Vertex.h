#pragma once
#include <array>
#include <GL/glew.h>
class Vertex
{
public:
	Vertex(std::array<GLfloat, 3> vert, std::array<GLfloat, 3> color);
	std::array<GLfloat, 3> vert;
	std::array<GLfloat, 3> color;
	std::array<GLfloat, 3> normal;
};


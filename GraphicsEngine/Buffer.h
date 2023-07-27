#pragma once
#include "GL/glew.h"
#include <vector>
class Buffer
{
protected:
	GLuint vertexBufferIndex = 0;
	GLuint colorBufferIndex = 0;
	const GLfloat* data;
	const GLfloat* colorData;
public:
	Buffer(const GLfloat* data, const GLfloat* colorData);
	virtual void bind() = 0;
};


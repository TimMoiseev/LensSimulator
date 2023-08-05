#pragma once
#include "GL/glew.h"
#include <vector>

class Buffer
{
protected:
	
	GLuint index;
	GLuint size;
public:
	Buffer(GLuint size);
	GLuint getIndex() const;
	/*Buffer(const GLfloat* data, const GLfloat* colorData);
	virtual void bind() = 0;*/
};


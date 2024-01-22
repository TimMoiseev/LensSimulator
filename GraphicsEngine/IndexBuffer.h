#pragma once
#include <GL/glew.h>
class IndexBuffer
{
	GLuint index = 0;
	GLuint size = 0;
public:
	GLuint getIndex() const { return index; };
	GLuint getSize() const { return size; }
	IndexBuffer(GLuint size, const void* data);
	void updateIndexBuffer(GLuint size, const void* data);
	~IndexBuffer();
};


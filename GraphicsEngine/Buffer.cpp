#include "pch.h"
#include "Buffer.h"

Buffer::Buffer(GLuint size): size{size}
{
	
}
GLuint Buffer::getIndex() const {
	return index;
}
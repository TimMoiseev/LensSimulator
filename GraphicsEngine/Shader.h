#pragma once
#include <GL/glew.h>
#include <string>
#include <fstream>
#include <sstream>
class Shader
{
	GLuint shaderId = 0;
	GLenum shaderType;
public:
	Shader(const char* shaderCodePath, GLenum shaderType);
	Shader() = delete;
	~Shader();
	GLuint getID() { return shaderId; }
	GLuint getType() { return shaderType; }
};


#pragma once
#include <GL/glew.h>
#include <vector>
#include "Shader.h"
class ShaderProgramManager
{
	std::vector<Shader*>* shaders;
	GLuint shaderProgramId = 0;
public:
	ShaderProgramManager() = delete;
	ShaderProgramManager(std::vector<Shader*>* shaders);
	GLuint getId();
	void use();
	
	~ShaderProgramManager();
	char* filePath = nullptr;
	
};


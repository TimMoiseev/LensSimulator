#pragma once
#include "ShaderProgramManager.h"
#include <map>
class ShaderSystem
{
	
public:
	ShaderProgramManager* shaderProgram;
	void bindUniformParameters(std::string name, GLfloat* parameterPointer);
	ShaderSystem() = delete;
	ShaderSystem(ShaderProgramManager* shaderProgram);
};


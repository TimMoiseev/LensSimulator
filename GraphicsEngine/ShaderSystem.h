#pragma once
#include "ShaderProgramManager.h"
#include <map>
class ShaderSystem
{
	ShaderProgramManager* shaderProgram;
	std::vector<std::string> uniformParameterNames;
	std::vector<GLfloat*> parameterPointers;
	std::vector<GLuint> parameterIDs;
	std::map<std::string, GLfloat*> namesToPointers;
	std::map<std::string, GLuint> namesToIDs;
public:
	void bindUniformParameters(std::string name);
	ShaderSystem() = delete;
	ShaderSystem(ShaderProgramManager* shaderProgram, std::vector<std::string> uniformParameterNames, std::vector<GLfloat*> parameterPointers);
};


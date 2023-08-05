#include "pch.h"
#include "ShaderSystem.h"
void ShaderSystem::bindUniformParameters(std::string name)
{
	glUniformMatrix4fv(namesToIDs[name], 1, GL_FALSE, namesToPointers[name]);
}
ShaderSystem::ShaderSystem(ShaderProgramManager* shaderProgram, std::vector<std::string> uniformParameterNames, std::vector<GLfloat*> parameterPointers) :
	shaderProgram{ shaderProgram }, 
	uniformParameterNames{ uniformParameterNames }, 
	parameterPointers{ parameterPointers } {
	/*for (int i = 0; i < uniformParameterNames.size(); i++) {
		parameterIDs.push_back(glGetUniformLocation(shaderProgram->getId(), uniformParameterNames[i].c_str()));
	}*/
	for (int i = 0; i < uniformParameterNames.size(); ++i) {
		namesToPointers.insert(std::pair<std::string, GLfloat*>(uniformParameterNames[i], parameterPointers[i]));
	}
	for (int i = 0; i < uniformParameterNames.size(); ++i) {
		namesToIDs.insert(std::pair<std::string, GLuint>(uniformParameterNames[i], glGetUniformLocation(shaderProgram->getId(), uniformParameterNames[i].c_str())));
	}
}
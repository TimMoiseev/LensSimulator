#include "pch.h"
#include "ShaderSystem.h"
void ShaderSystem::bindUniformParameters(std::string name, GLfloat* parameterPointer)
{
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram->getId(), name.c_str()), 1, GL_FALSE, parameterPointer);
}
ShaderSystem::ShaderSystem(ShaderProgramManager* shaderProgram) :
	shaderProgram{ shaderProgram } {
}
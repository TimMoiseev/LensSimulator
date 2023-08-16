#include "pch.h"
#include "ShaderProgramManager.h"

GLuint ShaderProgramManager::getId()
{
	return shaderProgramId;
}

ShaderProgramManager::ShaderProgramManager(std::vector<Shader*>* shaders) : shaders{shaders}
{
	GLint result = GL_FALSE;
	int InfoLogLength;
	shaderProgramId = glCreateProgram();
	/*for (Shader shader : shaders) {
		glAttachShader(shaderProgramId, shader.getID());
	}*/
	for (int i = 0; i < shaders->size(); i++) {
		glAttachShader(shaderProgramId, (*shaders)[i]->getID());
	}
	glLinkProgram(shaderProgramId);
	glGetProgramiv(shaderProgramId, GL_LINK_STATUS, &result);
	glGetProgramiv(shaderProgramId, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(shaderProgramId, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		fprintf(stdout, "%s\n", &ProgramErrorMessage[0]);
		result = GL_FALSE;
	}
	else {
		result = GL_TRUE;
	}
	for (int i = 0; i < (*shaders).size(); i++) {
		(*shaders)[i]->~Shader();
	}
}

void ShaderProgramManager::use()
{
	glUseProgram(shaderProgramId);
}

ShaderProgramManager::~ShaderProgramManager()
{
	for (Shader* shader : *shaders) {
		glDetachShader(shaderProgramId, shader->getID());
		shader->~Shader();
	}
	glUseProgram(0);
	glDeleteProgram(this->shaderProgramId);
}

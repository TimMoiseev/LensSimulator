#include "pch.h"
#include "Shader.h"

Shader::Shader(const char* shaderCodePath, GLenum shaderType) : shaderType{shaderType}
{
	shaderId = glCreateShader(shaderType);
    std::string shaderCode;
    std::ifstream shaderStream(shaderCodePath, std::ios::in);
    if (shaderStream.is_open())
    {
        std::stringstream sstr;
        sstr << shaderStream.rdbuf();
        shaderCode = sstr.str();
        shaderStream.close();
    }
    GLint Result = GL_FALSE;
    int InfoLogLength;

    char const* sourcePointer = shaderCode.c_str();
    glShaderSource(shaderId, 1, &sourcePointer, NULL);
    glCompileShader(shaderId);

    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0) {
        /*std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
        glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
        fprintf(stdout, "%sn", &VertexShaderErrorMessage[0]);*/
        return;
    }

}

Shader::~Shader()
{
    glDeleteShader(shaderId);
}

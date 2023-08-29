#pragma once
#include "Scene.h"
#include <GL/glew.h>
#include <glm/ext/matrix_transform.hpp>
class Primitive:
	public Scene
{
public:
	void virtual createModel() {};
	const GLfloat* getObjectMatrix();
	std::vector<Vertex>* vertices = new std::vector<Vertex>();
	std::vector<GLuint>* indices = new std::vector<GLuint>();
protected:
	
	glm::mat4 objectMatrix = glm::mat4(1.0f); //objects translation and rotation
	void virtual translate(glm::vec3 position);
	void virtual rotate(glm::vec3 axis, GLfloat angle);
	
};


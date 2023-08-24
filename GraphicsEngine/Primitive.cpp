#include "pch.h"
#include "Primitive.h"


void Primitive::translate(glm::vec3 position)
{
	objectMatrix = glm::translate(objectMatrix, position);
}

void Primitive::rotate(glm::vec3 axis, GLfloat angle)
{
	objectMatrix = glm::rotate(objectMatrix, glm::radians(angle), axis);
}

const GLfloat* Primitive::getObjectMatrix()
{
	return &objectMatrix[0][0];
}

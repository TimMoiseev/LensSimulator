#pragma once
#include "Primitive.h"
class Line:
	public Primitive
{
	glm::vec3 firstPoint;
	glm::vec3 secondPoint;
	glm::vec3 color;
	void createModel() override;
public:
	Line(glm::vec3 point1, glm::vec3 point2, glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f));
	void update(float duration) override;
};


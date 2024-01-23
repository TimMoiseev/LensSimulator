#pragma once
#include "Primitive.h"
#include <glm/glm.hpp>
#include "glm/gtc/quaternion.hpp"
#include <glm/gtx/vector_angle.hpp>
using quat = glm::quat;
using vec4 = glm::vec4;
class RingStrip: public Primitive
{
private:
	void createModel();
	float d = 0.0f;
	float h = 0.0f;
	int n = 0;
	vec3 o{ 0.0f, 0.0f, 0.0f };
	vec3 p{ 0.0f, 0.0f, 0.0f };


public:
	RingStrip() = delete;
	RingStrip(float diameter, float height,int segmentCount, vec3 orientationm, vec3 position);
	void update(float dTime) override;
	void update(GLfloat d, GLfloat h);

};


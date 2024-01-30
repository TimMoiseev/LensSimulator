#pragma once
#include "Primitive.h"
#include "glm/gtc/quaternion.hpp"
#include <glm/gtx/vector_angle.hpp>

using quat = glm::quat;
using vec4 = glm::vec4;

class FlatDisk : public Primitive
{
	double d = 0.0;
	vec3 o = vec3();
	vec3 p = vec3();
	void createModel();
public:
	FlatDisk() = delete;
	FlatDisk(double d, vec3 orientation, vec3 position);
};


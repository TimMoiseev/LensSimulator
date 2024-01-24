#pragma once
#include "Primitive.h"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/quaternion.hpp"
#include <glm/gtx/vector_angle.hpp>
class SphericalCap
	: public Primitive
{
private:
	void createModel() override;
	int uCount = 0;
	int vCount = 0;
	float R = 0.0f;
	float diameter = 0.0f;
	vec3 o{ 0.0f, 0.0f, 0.0f };
	vec3 p{ 0.0f, 0.0f, 0.0f };
	float alpha = 0.0f;
	float maxAlpha = 0.0f;
	float maxBeta = 360.0f;
	float dAlpha = 0.0f;
	float dBeta = 0.0f;

public:
	SphericalCap(
		float R = 30.0f,
		float diameter = 60.0f,
		vec3 orientation = vec3{ 1.0f, 0.0f, 0.0f },
		vec3 position = vec3{ 0.0f, 0.0f, 0.0f },
		bool forwardDirecton = true,
		int uCount = 128,
		int vCount = 128);
	void update(float dTime) override;
};


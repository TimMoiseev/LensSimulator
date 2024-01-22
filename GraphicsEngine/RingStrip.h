#pragma once
#include "Primitive.h"
#include "math.h"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/quaternion.hpp"

class RingStrip: public Primitive
{
private:
	void createModel();
	float d = 0.0f;
	float h = 0.0f;
	int n = 0;
public:
	RingStrip() = delete;
	RingStrip(float diameter, float height,int segmentCount, vec3 orientation);
	void update(float dTime) override;
	void update(GLfloat d, GLfloat h);

};


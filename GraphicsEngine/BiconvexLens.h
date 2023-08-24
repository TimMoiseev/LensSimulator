#pragma once
#include "Primitive.h"
#include "math.h"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/quaternion.hpp"
class BiconvexLens
	: public Primitive
{
private:
	void createModel() override;
	int uCount = 0;
	int vCount = 0;
	GLfloat R = 0.0f;
	GLfloat diameter = 0.0f;
	GLfloat h = 0.0f;
	GLfloat m = 0.0f;
	GLfloat alpha = 0.0f;
	GLfloat maxAlpha = 0.0f;
	GLfloat maxBeta = 360.0f;
	GLfloat dAlpha = 0.0f;
	GLfloat dBeta = 0.0f;

public:
	BiconvexLens(
		GLfloat R = 60.0f, 
		GLfloat diameter = 60.0f, 
		GLfloat m = 0.0f, 
		int uCount = 128,
		int vCount = 128);
	void update(float dTime) override;
};


#include "pch.h"
#include "RingStrip.h"

void RingStrip::createModel()
{
	for (int i = -n; i < n; ++i) {
		vertices->push_back(Vertex{ {d * glm::cos(2.0f * glm::pi<float>() * i / n), d * glm::sin(2.0f * glm::pi<float>() * i / n),  h / 2.0f},{255, 255, 255} });
		vertices->push_back(Vertex{ {d * glm::cos(2.0f * glm::pi<float>() * i / n), d * glm::sin(2.0f * glm::pi<float>() * i / n), -h / 2.0f},{255, 255, 255} });
	}
	for (int i = 0; i < 2*n; ++i) {
		indices->push_back(i);
		indices->push_back(i + 1);
		indices->push_back(i + 2);
	}
}

RingStrip::RingStrip(float diameter, float height, int segmentCount, vec3 orientation) : 
	d{diameter}, h{height}, n{segmentCount}
{
	createModel();
	createBuffer(vertices, indices);
}

void RingStrip::update(float dTime)
{
}

void RingStrip::update(GLfloat d, GLfloat h)
{
}

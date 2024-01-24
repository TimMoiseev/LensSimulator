#include "pch.h"
#include "RingStrip.h"

void RingStrip::createModel()
{
	
	vec3 zAxis{0.0f, 0.0f, 1.0f};
	vec3 rotAxis = glm::cross(zAxis, o);
	float angle = glm::angle(zAxis, o);
	quat rot = glm::angleAxis(angle, glm::normalize(rotAxis));
	for (int i = -n; i < n; ++i) {
		vec4 ringDot = rot * vec4(vec3(0.5 * d * glm::cos(2.0f * glm::pi<float>() * i / n) , 0.5 * d * glm::sin(2.0f * glm::pi<float>() * i / n), h / 2.0f), 0.0); //quat*dot*conjugate_quat - так нельзя, в glm поворот делается так quat*dot
		vec4 oppositeRingDot = rot * vec4(vec3(0.5 * d * glm::cos(2.0f * glm::pi<float>() * i / n), 0.5 * d * glm::sin(2.0f * glm::pi<float>() * i / n), -h / 2.0f), 0.0);
		vertices->push_back(Vertex{ { ringDot.x + p.x, ringDot.y + p.y, ringDot.z + p.z },{255, 255, 255} });
		vertices->push_back(Vertex{ {oppositeRingDot.x + p.x, oppositeRingDot.y + p.y, oppositeRingDot.z + p.z},{255, 255, 255} });
	}
	for (int i = 0; i < 2*n; ++i) {
		indices->push_back(i);
		indices->push_back(i + 1);
		indices->push_back(i + 2);
	}
}

RingStrip::RingStrip(float diameter, float height, int segmentCount, vec3 orientation, vec3 position) : 
	d{ diameter }, h{ height }, n{ segmentCount }, o{glm::normalize(orientation)}, p{position}
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

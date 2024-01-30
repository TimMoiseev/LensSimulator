#include "pch.h"
#include "FlatDisk.h"

void FlatDisk::createModel()
{
	int n = 100;
	vec3 zAxis{ 0.0f, 0.0f, 1.0f };
	vec3 rotAxis = glm::cross(zAxis, o);
	float angle = glm::angle(zAxis, o);
	quat rot{};
	if (rotAxis != vec3{ 0.0,0.0,0.0 }) {
		rot = glm::angleAxis(angle, glm::normalize(rotAxis));
	}
	else {
		rot = quat{ 0.0,0.0,0.0,0.0 };
	}
	vertices->push_back(Vertex{ {p.x, p.y, p.z},{1.0, 1.0, 1.0}, {o.x, o.y, o.z} });
	for (int i = -n; i < n; i++) {
		vec4 ringDot =
			rot * vec4(vec3(0.5 * d * glm::cos(2.0f * glm::pi<float>() * i / n), 0.5 * d * glm::sin(2.0f * glm::pi<float>() * i / n), 0.0), 0.0);
		vertices->push_back(Vertex({ ringDot.x + p.x, ringDot.y + p.y, ringDot.z + p.z }, {1.0, 1.0, 1.0}, {o.x, o.y, o.z}));
	}
	indices->push_back(0);
	for (int i = 1; i < 2 * n; i++) {
		indices->push_back(i);
	}
}

FlatDisk::FlatDisk(double d, vec3 orientation, vec3 position) : d{ d }, o{ glm::normalize(orientation) }, p{position}
{
	geometryType = GL_TRIANGLE_FAN;
	createModel();
	createBuffer(vertices, indices);
}


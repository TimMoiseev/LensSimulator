#include "pch.h"
#include "SphericalCap.h"

using glm::vec3;
using glm::quat;
using glm::vec4;

void SphericalCap::createModel()
{
	vec3 zAxis = vec3(0.0f, 0.0f, 1.0f);
	vec3 xAxis = vec3(1.0f, 0.0f, 0.0f);
	quat quatZ{
		cos(glm::radians(dAlpha/2.0f)),
		zAxis.x * sin(glm::radians(dAlpha / 2.0f)),
		zAxis.y * sin(glm::radians(dAlpha / 2.0f)),
		zAxis.z * sin(glm::radians(dAlpha / 2.0f))
	};
	quat quatX{
		cos(glm::radians(dBeta / 2.0f)),
		xAxis.x * sin(glm::radians(dBeta / 2.0f)),
		xAxis.y * sin(glm::radians(dBeta / 2.0f)),
		xAxis.z * sin(glm::radians(dBeta / 2.0f))
	};
	vertices->push_back(Vertex({ R, 0.0, 0.0 }, { 1.0f, 1.0f, 1.0f }));
	auto mat4Z = quatZ.quat::operator glm::mat<4, 4, glm::f32, glm::packed_highp>();
	auto mat4X = quatX.quat::operator glm::mat<4, 4, glm::f32, glm::packed_highp>();
	
	vec3 rotAxis = glm::cross(xAxis, o);
	float angle = glm::angle(xAxis, o);
	quat rot = glm::angleAxis(angle, glm::normalize(rotAxis));
	for (GLint u = 0; u < uCount; u += 1) {
		auto vec4Z = (mat4Z * vec4(vec3(
			(vertices->begin() + (u == 0 ? u * uCount : vertices->size() - uCount))->vert[0],
			(vertices->begin() + (u == 0 ? u * uCount : vertices->size() - uCount))->vert[1],
			(vertices->begin() + (u == 0 ? u * uCount : vertices->size() - uCount))->vert[2]),
			0.0f));
		vertices->push_back(Vertex({ vec4Z.x, vec4Z.y, vec4Z.z }, vertices->begin()->color));

		for (GLuint v = 0; v < uCount-1; v += 1) {
			auto vec4X = (mat4X * vec4(vec3(
				(vertices->end() - 1)->vert[0],
				(vertices->end() - 1)->vert[1],
				(vertices->end() - 1)->vert[2]),
				0.0f));
			vertices->push_back(Vertex({ vec4X.x, vec4X.y, vec4X.z }, vertices->begin()->color));
			if (u == 0) {
				if (v == 0) {
					indices->push_back(0);
					indices->push_back(1);
					indices->push_back(uCount);
				}
				indices->push_back(0);
				indices->push_back(v + 1);
				indices->push_back(v + 2);
			} else {
				indices->push_back(vertices->size() - uCount - 2);
				indices->push_back(vertices->size() - 2);
				indices->push_back(vertices->size() + 1 - 2);
				if (v == uCount - 2) {
					indices->push_back(vertices->size() - uCount - 2 + 1);
					indices->push_back(vertices->size() - 2 + 1);
					indices->push_back(vertices->size() - uCount);
				}

				indices->push_back(vertices->size() - uCount - 2);
				indices->push_back(vertices->size() - uCount - 2 + 1);
				indices->push_back(vertices->size() + 1 - 2);
				if (v == uCount - 2) {
					indices->push_back(vertices->size() - uCount - 2 + 1);
					indices->push_back(vertices->size() - uCount);
					indices->push_back(vertices->size() - 2 * uCount);
				}
			}
		}
	}
	mat4 moveToZero = glm::translate(mat4(1.f), vec3(-R, 0.0, 0.0));
	for (int i = 0; i < vertices->size(); ++i) {
		auto newPos = rot*(moveToZero * vec4(vertices->at(i).vert[0], vertices->at(i).vert[1], vertices->at(i).vert[2], 1.0));
		vertices->at(i).vert = { newPos.x + p.x, newPos.y + p.y, newPos.z + p.z };
	}
}

SphericalCap::SphericalCap(float R, float diameter, vec3 orientation, vec3 position, bool forwardDirection, int uCount, int vCount) :
	R{ R },
	diameter{ diameter },
	o{ glm::normalize(forwardDirection ? orientation : -orientation) },
	p{ position + vec3{0.0, (R - glm::sqrt(glm::pow(R, 2.0) - glm::pow(diameter, 2.0) / 4.0))*((forwardDirection ? 1.0 : -1.0)), 0.0}},
	alpha{ (180.f / glm::pi<float>()) * 2.0f * std::asinf(diameter / (2.0f * R)) },
	maxAlpha{ alpha / 2.0f },
	uCount{ uCount },
	vCount{ vCount },
	dAlpha{ maxAlpha / uCount },
	dBeta{ maxBeta / vCount}
{
	createModel();
	createBuffer(vertices, indices);

}

void SphericalCap::update(float dTime){}
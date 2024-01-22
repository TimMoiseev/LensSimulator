#include "pch.h"
#include "SphericalCap.h"

using glm::vec3;
using glm::quat;
using glm::vec4;

void SphericalCap::createModel()
{
	vec3 aroundZ = vec3(0.0f, 0.0f, 1.0f);
	vec3 aroundX = vec3(1.0f, 0.0f, 0.0f);
	quat quatZ{
		cos(glm::radians(dAlpha/2.0f)),
		aroundZ.x * sin(glm::radians(dAlpha / 2.0f)),
		aroundZ.y * sin(glm::radians(dAlpha / 2.0f)),
		aroundZ.z * sin(glm::radians(dAlpha / 2.0f))
	};
	quat quatX{
		cos(glm::radians(dBeta / 2.0f)),
		aroundX.x * sin(glm::radians(dBeta / 2.0f)),
		aroundX.y * sin(glm::radians(dBeta / 2.0f)),
		aroundX.z * sin(glm::radians(dBeta / 2.0f))
	};
	vertices->push_back(Vertex({ R, 0.0, 0.0 }, { 1.0f, 1.0f, 1.0f }));
	auto mat4Z = quatZ.quat::operator glm::mat<4, 4, glm::f32, glm::packed_highp>();
	auto mat4X = quatX.quat::operator glm::mat<4, 4, glm::f32, glm::packed_highp>();

	for (GLint u = 0; u < uCount; u += 1) {
		auto newVec4Z = (mat4Z * vec4(vec3(
			(vertices->begin() + (u == 0 ? u * uCount : vertices->size() - uCount))->vert[0],
			(vertices->begin() + (u == 0 ? u * uCount : vertices->size() - uCount))->vert[1],
			(vertices->begin() + (u == 0 ? u * uCount : vertices->size() - uCount))->vert[2]),
			0.0f));
		vertices->push_back(Vertex({ newVec4Z.x, newVec4Z.y, newVec4Z.z }, vertices->begin()->color));

		for (GLuint v = 0; v < uCount-1; v += 1) {
			auto newVec4X = (mat4X * vec4(vec3(
				(vertices->end() - 1)->vert[0],
				(vertices->end() - 1)->vert[1],
				(vertices->end() - 1)->vert[2]),
				0.0f));
			vertices->push_back(Vertex({ newVec4X.x, newVec4X.y, newVec4X.z }, vertices->begin()->color));
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
		auto newPos = moveToZero * vec4(vertices->at(i).vert[0], vertices->at(i).vert[1], vertices->at(i).vert[2], 1.0);
		vertices->at(i).vert = { newPos.x, newPos.y, newPos.z };
	}
}

SphericalCap::SphericalCap(GLfloat R, GLfloat diameter, GLfloat m, int uCount, int vCount) :
	R{ R },
	diameter{ diameter },
	m{ m },
	h{ 2.0f * (R - sqrt(pow(R, 2.0f) - pow(diameter, 2.0f) / 4.0f)) + m },
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

void SphericalCap::update(GLfloat r, GLfloat d, GLfloat h)
{
	R = r;
	diameter = d;
	m = h;
	delete indices;
	delete vertices;
	vertices = new std::vector<Vertex>();
	indices = new std::vector<GLuint>();
	createModel();
	createBuffer(vertices, indices);
}

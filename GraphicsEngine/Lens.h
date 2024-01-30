#include <glm/fwd.hpp>
#include "SphericalCap.h"
#include "RingStrip.h"
#include "OpticElement.h"
#include "FlatDisk.h"
#pragma once
using vec3 = glm::vec3;

class Lens: public OpticElement
{
private:
	 
	SphericalCap* leftCap = nullptr;
	SphericalCap* rightCap = nullptr;
	RingStrip* ringStrip = nullptr;
	FlatDisk* disk = nullptr;
	float d = 0.0f;
	float r1 = 0.0f;
	float r2 = 0.0f;
	float h = 0.0f;
	vec3 o{ 0.0f, 0.0f, 0.0f };
	vec3 p{ 0.0f, 0.0f, 0.0f };
	void createModel();
public:
	Lens() = delete;
	Lens(float diameter, float radius1, float radius2, float flatSegmentLength, vec3 orientation, vec3 position, OpticElementType type = OpticElementType::DoubleConvex, int id = 0);
	~Lens();
	const std::vector<Primitive*> getModels() override;
	bool changeProperties(float d, float r1, float r2, float h, OpticElementType type) override;
	void move(vec3 pos) override;
};


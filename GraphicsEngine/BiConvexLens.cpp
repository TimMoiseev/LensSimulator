#include "pch.h"
#include "BiConvexLens.h"

void BiConvexLens::createModel()
{
	
	vec3 hOffset = h / 2.0f * o;
	leftCap = new SphericalCap(r1, d, o,  + hOffset);
	rightCap = new SphericalCap(r2, d, -o, - hOffset);
	ringStrip = new RingStrip(d, h, 100, o, vec3{0.0,0.0,0.0});
}

BiConvexLens::BiConvexLens(float diameter, float radius1, float radius2, float flatSegmentLength, vec3 orientation, vec3 position, int id):
	d{diameter},
	r1{radius1},
	r2{radius2}, 
	h{flatSegmentLength}, 
	o{glm::normalize(orientation)}, 
	p{position}
{
	OpticElement::id = id;
	OpticElement::type = OpticElementType::DoubleConvex;
	createModel();
}

BiConvexLens::~BiConvexLens()
{
	delete leftCap;
	delete rightCap;
	delete ringStrip;
}

const std::vector<Primitive*> BiConvexLens::getModels()
{
	return std::vector{(Primitive*)leftCap, (Primitive*)rightCap, (Primitive*)ringStrip};
}

bool BiConvexLens::changeProperties(float d, float r1, float r2, float h, OpticElementType type)
{
	if (this->d != d) {
		this->d = d;
		needChange = true;
	}
	if (this->r1 != r1) {
		this->r1 = r1;
		needChange = true;
	}
	if (this->r2 != r2) {
		this->r2 = r2;
		needChange = true;
	}
	if (this->h != h) {
		this->h = h;
		needChange = true;
	}
	if (needChange) {
		delete leftCap;
		delete rightCap;
		delete ringStrip;
		createModel();
		leftCap->translate(p);
		rightCap->translate(p);
		ringStrip->translate(p);
		needChange = false;
	}
	return false;
}

void BiConvexLens::move(vec3 pos)

{
	leftCap->translate(pos);
	rightCap->translate(pos);
	ringStrip->translate(pos);
	p = pos;
}

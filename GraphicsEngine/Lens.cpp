#include "pch.h"
#include "Lens.h"

void Lens::createModel()
{
	vec3 hOffset = h / 2.0f * o;
	switch (OpticElement::type)
	{
	case OpticElementType::DoubleConvex:
		leftCap = new SphericalCap(r1, d, o, +hOffset);
		rightCap = new SphericalCap(r2, d, -o, -hOffset);
		ringStrip = new RingStrip(d, h, 100, o, vec3{ 0.0,0.0,0.0 });
		break;
	case OpticElementType::DoubleConcave:
		leftCap = new SphericalCap(r1, d, -o, +hOffset);
		rightCap = new SphericalCap(r2, d, o, -hOffset);
		ringStrip = new RingStrip(d, h, 100, o, vec3{ 0.0,0.0,0.0 });
		break;
	case OpticElementType::PlanoConvex:
		disk = new FlatDisk(d, o, hOffset);
		rightCap = new SphericalCap(r2, d, -o, -hOffset);
		ringStrip = new RingStrip(d, h, 100, o, vec3{ 0.0,0.0,0.0 });
		break;
	case OpticElementType::PlanoConcave:
		disk = new FlatDisk(d, o, hOffset);
		rightCap = new SphericalCap(r2, d, o, -hOffset);
		ringStrip = new RingStrip(d, h, 100, o, vec3{ 0.0,0.0,0.0 });
		break;
	case OpticElementType::PositiveMeniscus:
		leftCap = new SphericalCap(r1, d, o, +hOffset);
		rightCap = new SphericalCap(r2, d, o, -hOffset);
		ringStrip = new RingStrip(d, h, 100, o, vec3{ 0.0,0.0,0.0 });
		break;
	case OpticElementType::NegativeMeniscus:
		leftCap = new SphericalCap(r1, d, -o, +hOffset);
		rightCap = new SphericalCap(r2, d, -o, -hOffset);
		ringStrip = new RingStrip(d, h, 100, o, vec3{ 0.0,0.0,0.0 });
		break;
	default:
		break;
	}
}

Lens::Lens(float diameter, float radius1, float radius2, float flatSegmentLength, vec3 orientation, vec3 position, OpticElementType type, int id):
	OpticElement(id, type),
	d{diameter},
	r1{radius1},
	r2{radius2}, 
	h{flatSegmentLength}, 
	o{glm::normalize(orientation)}, 
	p{position}
{
	createModel();
}

Lens::~Lens()
{
	delete disk;
	delete leftCap;
	delete rightCap;
	delete ringStrip;
}

const std::vector<Primitive*> Lens::getModels()
{
	return std::vector{(Primitive*)leftCap, (Primitive*)rightCap, (Primitive*)ringStrip, (Primitive*)disk};
}

bool Lens::changeProperties(float d, float r1, float r2, float h, OpticElementType type)
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
		move(p);
		needChange = false;
	}
	return false;
}

void Lens::move(vec3 pos)
{
	if (leftCap != nullptr) {
		leftCap->translate(pos);
		p = pos;
	}
	if (rightCap != nullptr) {
		rightCap->translate(pos);
		p = pos;
	}
	if (ringStrip != nullptr) {
		ringStrip->translate(pos);
		p = pos;
	}
	if (disk != nullptr) {
		disk->translate(pos);
		p = pos;
	}
}

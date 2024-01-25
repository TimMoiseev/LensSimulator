#include "pch.h"
#include "BiConvexLens.h"

BiConvexLens::BiConvexLens(float diameter, float radius1, float radius2, float flatSegmentLength, vec3 orientation, vec3 position):
	d{diameter},
	r1{radius1},
	r2{radius2}, 
	h{flatSegmentLength}, 
	o{glm::normalize(orientation)}, 
	p{position}
{
	vec3 hOffset = h / 2.0f * o;
	leftCap = new SphericalCap(r1, d, o, p + hOffset);
	rightCap = new SphericalCap(r2, d, -o, p - hOffset);
	ringStrip = new RingStrip(d, h, 100, o, p);
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

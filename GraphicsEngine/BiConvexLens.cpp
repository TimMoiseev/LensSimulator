#include "pch.h"
#include "BiConvexLens.h"

BiConvexLens::BiConvexLens(float diameter, float radius1, float radius2, float flatSegmentLength, vec3 orientation, vec3 position):
	d{diameter},
	r1{radius1},
	r2{radius2}, 
	h{flatSegmentLength}, 
	o{orientation}, 
	p{position}
{
	leftCap = new SphericalCap(r1, d, o, p + vec3{0.0, -h/2.0, 0.0}, false);
	rightCap = new SphericalCap(r2, d, o, p + vec3{0.0, h/2.0, 0.0}, true);
	ringStrip = new RingStrip(d, h, 100, o, vec3{0.0, 0.0, 0.0} + p);
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

#pragma once
#include <vector>
#include "Primitive.h"

enum OpticElementType {
    DoubleConvex,
    PlanoConvex,
    PositiveMeniscus,
    NegativeMeniscus,
    PlanoConcave,
    DoubleConcave
};
class OpticElement
{
public:
	OpticElement() = delete;
    OpticElement(int id, OpticElementType type) : id{ id }, type{type} {};
    virtual const std::vector<Primitive*> getModels() { return std::vector<Primitive*>{}; }
    virtual bool changeProperties(float d, float r1, float r2, float h, OpticElementType type) { return false; };
    virtual void move(vec3 pos) {};
    OpticElementType type;
    int id = 0;
protected:
    bool needChange = false;
};


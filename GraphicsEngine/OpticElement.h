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
	OpticElement() {};
    virtual const std::vector<Primitive*> getModels() { return std::vector<Primitive*>{}; }
    virtual bool changeProperties(float d, float r1, float r2, float h, OpticElementType type = OpticElementType::DoubleConvex) { return false; };
    OpticElementType type = OpticElementType::DoubleConvex;
    int id = 0;
};


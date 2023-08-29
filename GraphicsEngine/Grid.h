#pragma once
#include "Primitive.h"
#include "Line.h"
class Grid:
	public Primitive
{

	int n = 0;
	int m = 0;
	float step = 0.0;
	void createModel() override;
public:
	Grid(int n = 10, float step = 10.0f);
	void update(float duration) override;
};


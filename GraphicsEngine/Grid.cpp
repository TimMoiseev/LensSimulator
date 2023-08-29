#include "pch.h"
#include "Grid.h"



void Grid::createModel()
{
	int j = 0;
	for (int i = -n; i < n+1; ++i) {
		vertices->push_back(Vertex({ float(i * step), -step * n, 0.0 }, { 1.0, 1.0, 1.0 }));
		vertices->push_back(Vertex({ float(i * step), step * n, 0.0 }, { 1.0, 1.0, 1.0 }));
		indices->push_back(j);
		indices->push_back(j + 1);
		vertices->push_back(Vertex({ -step * n, float(i * step), 0.0 }, { 1.0, 1.0, 1.0 }));
		vertices->push_back(Vertex({ step * n, float(i * step), 0.0 }, { 1.0, 1.0, 1.0 }));
		j += 2;
		indices->push_back(j);
		indices->push_back(j + 1);
		j += 2;
	}
}

Grid::Grid(int n, float step): n{n}, step{step}
{
	geometryType = Lines;
	createModel();
	createBuffer(vertices, indices);
}

void Grid::update(float duration)
{
}

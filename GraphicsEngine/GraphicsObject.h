#pragma once
#include <vector>
#include "Scene.h"

class GraphicsObject
{
	std::vector<Scene*> SceneObjects;
public:
	void update(float dTime);
	void add(Scene* obj);
};


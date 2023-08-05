#include "pch.h"
#include "GraphicsObject.h"

void GraphicsObject::update(float dTime)
{
	for (Scene* sObj : SceneObjects) {
		sObj->objectMatrix = glm::rotate(sObj->objectMatrix, glm::radians(0.0000001f*dTime), glm::vec3(0.0f, 0.0f, 1.0f));
	}
}

void GraphicsObject::add(Scene* obj)
{
	SceneObjects.push_back(obj);
}



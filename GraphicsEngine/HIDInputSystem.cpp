#include "pch.h"
#include "HIDInputSystem.h"

void HIDInputSystem::setActualdXdY(int x, int y)
{
	dX = x;
	dY = y;
}

void HIDInputSystem::getActualdXdY(int& dx, int& dy)
{
	dx = dX;
	dy = dY;
}

HIDInputSystem::HIDInputSystem(MessageProcessingSystem* system) : messageSystem{system}
{
	messageSystem->mouseDragFun([&](int x, int y) { setActualdXdY(x, y); });
}

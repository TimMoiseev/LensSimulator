#include "pch.h"
#include "HIDInputSystem.h"

void HIDInputSystem::setActualdXdY(int x, int y)
{
	dX = x;
	dY = y;
}

void HIDInputSystem::setActualZDelta(int z)
{
	zDelta = z;
}

void HIDInputSystem::getActualdXdY(int& dx, int& dy)
{
	dx = dX;
	dy = dY;
}

void HIDInputSystem::getActualZDelta(int& z)
{
	z = zDelta;
	zDelta = 0;
}

HIDInputSystem::HIDInputSystem(MessageProcessingSystem* system) : messageSystem{system}
{
	messageSystem->mouseDragFun([&](int x, int y) { setActualdXdY(x, y); });
	messageSystem->setMouseWheelCallback([&](int z) {setActualZDelta(z); });
}

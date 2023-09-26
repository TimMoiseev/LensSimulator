#pragma once
#include "MessageProcessingSystem.h"
class HIDInputSystem
{
	int dX = 0;
	int dY = 0;
	int zDelta = 0;
	MessageProcessingSystem* messageSystem = nullptr;
	void setActualdXdY(int x, int y);
	void setActualZDelta(int zDelta);
public:
	
	void getActualdXdY(int& dx, int& dy);
	void getActualZDelta(int& zDelta);
	HIDInputSystem() = delete;
	HIDInputSystem(MessageProcessingSystem* system);
	~HIDInputSystem() = default;
};


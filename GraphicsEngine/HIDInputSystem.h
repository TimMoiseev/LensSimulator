#pragma once
#include "MessageProcessingSystem.h"
class HIDInputSystem
{
	int dX = 0;
	int dY = 0;
	MessageProcessingSystem* messageSystem = nullptr;
public:
	void setActualdXdY(int x, int y);
	void getActualdXdY(int& dx, int& dy);
	HIDInputSystem() = delete;
	HIDInputSystem(MessageProcessingSystem* system);
	~HIDInputSystem() = default;
};


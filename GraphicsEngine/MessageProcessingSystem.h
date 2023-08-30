#pragma once
#include <string>

using std::string;

class MessageProcessingSystem
{
	
	string currentMessage;
	MessageProcessingSystem();
public:
	string getCurrentMessage();
	static MessageProcessingSystem* create();
	void destroyMessageProcessingSystem(MessageProcessingSystem* target);
	void reciveMessage(char* message);
};

extern "C" __declspec(dllexport) MessageProcessingSystem* createMessageProcessingSystem();
extern "C" __declspec(dllexport) void reciveMessageInternal(MessageProcessingSystem * target, char* message);
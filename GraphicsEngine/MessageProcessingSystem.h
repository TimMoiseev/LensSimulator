#pragma once
#include <string>
#include <mutex>
#include <nlohmann/json.hpp>

using std::string;
using std::mutex;
using json = nlohmann::json;

class MessageProcessingSystem
{
	json currentMessage;
	mutex mtx;
	MessageProcessingSystem();
public:
	json getCurrentMessage();
	static MessageProcessingSystem* create();
	void destroyMessageProcessingSystem(MessageProcessingSystem* target);
	void reciveMessage(json message);
};

extern "C" __declspec(dllexport) MessageProcessingSystem* createMessageProcessingSystem();
extern "C" __declspec(dllexport) void reciveMessageInternal(MessageProcessingSystem * target, char* message);
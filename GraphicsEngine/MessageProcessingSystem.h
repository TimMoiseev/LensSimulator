#pragma once
#include <string>
#include <mutex>
#include <nlohmann/json.hpp>
#include <queue>



using RESIZEFUNPOINTER = void (*)(int, int);
using std::string;
using std::mutex;
using json = nlohmann::json;
using std::queue;
using std::list;
using std::function;



enum MessageType {
	Stop = 1,
	Resize = 2,
	MouseDrag = 4
};


class MessageProcessingSystem
{
	queue<json> messages;
	json currentMessage;
	mutex mtx;
	MessageProcessingSystem();
	function<void(void)> stopFunPointer = nullptr;
	RESIZEFUNPOINTER resizeFunPointer = nullptr;
public:
	void setStopCallback(function<void(void)> f);
	void setResizeCallback(void (*)(int, int));
	bool process();
	json getCurrentMessage();
	static MessageProcessingSystem* create();
	void destroyMessageProcessingSystem(MessageProcessingSystem* target);
	void reciveMessage(json message);
};

extern "C" __declspec(dllexport) MessageProcessingSystem* createMessageProcessingSystem();
extern "C" __declspec(dllexport) void reciveMessageInternal(MessageProcessingSystem * target, char* message);

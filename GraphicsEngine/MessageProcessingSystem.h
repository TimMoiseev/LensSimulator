#pragma once
#include <string>
#include <mutex>
#include <nlohmann/json.hpp>
#include <queue>
#include "OpticElement.h"

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
	function<void(int, int)> mouseDragPointer = nullptr;
	function<void(int)> mouseWheelPointer = nullptr;
	function<void(int, int)> resizeFunPointer = nullptr;
	function<void(string, int, float, float, float, float, float, float, float)> changeLensFunPointer = nullptr;
public:
	void setStopCallback(function<void(void)> f);
	void setResizeCallback(function<void(int,int)> f);
	void setMouseWheelCallback(function<void(int)> f);
	void setChangeLensCallBack(function<void(string, int, float, float, float, float, float, float, float)> f);
	void mouseDragFun(function<void(int,int)> f);
	bool process();
	json getCurrentMessage();
	static MessageProcessingSystem* create();
	void destroyMessageProcessingSystem(MessageProcessingSystem* target);
	void reciveMessage(json message);
};

extern "C" __declspec(dllexport) MessageProcessingSystem* createMessageProcessingSystem();
extern "C" __declspec(dllexport) void reciveMessageInternal(MessageProcessingSystem * target, char* message);



#include "pch.h"
#include "MessageProcessingSystem.h"

MessageProcessingSystem::MessageProcessingSystem()
{
}
void MessageProcessingSystem::destroyMessageProcessingSystem(MessageProcessingSystem* target)
{
	target->~MessageProcessingSystem();
}
void MessageProcessingSystem::reciveMessage(json message){
	mtx.lock();
	messages.push(message);
	mtx.unlock();
}

void MessageProcessingSystem::setStopCallback(function<void(void)> f)
{
	stopFunPointer = f;
}

void MessageProcessingSystem::setResizeCallback(void (*f)(int, int))
{
	resizeFunPointer = f;
}

void MessageProcessingSystem::mouseDragFun(function<void(int, int)> f)
{
	mouseDragPointer = f;
}

bool MessageProcessingSystem::process()
{

	auto message = getCurrentMessage();
	if (!message.empty()) {
		if (message["Type"].template get<std::string>() == "Resize") {
			resizeFunPointer(message["Width"].template get<UINT>(), message["Height"].template get<UINT>());
			return true;
		}
		else if (message["Type"].template get<std::string>() == "OnOffCommand") {
			if (message["CommandType"].template get<std::string>() == "Stop"){
				if (stopFunPointer != nullptr) {
					stopFunPointer();
				}
			}
		}
		else if (message["Type"].template get<std::string>() == "MouseDrag") {
			int x = message["X"].template get<UINT>();
			int y = message["Y"].template get<UINT>();
			if (stopFunPointer != nullptr) {
				mouseDragPointer(x, y);
			}
		}
	}
	
	return false;
}
json MessageProcessingSystem::getCurrentMessage() {
	if (!messages.empty()) {
		currentMessage = messages.front();
		messages.pop();
	}
	else {
		currentMessage = nullptr;
	}
	
	return MessageProcessingSystem::currentMessage;
}
MessageProcessingSystem* createMessageProcessingSystem()
{
	return MessageProcessingSystem::create();
}

MessageProcessingSystem* MessageProcessingSystem::create() {
	static MessageProcessingSystem myHandle;
	return &myHandle;
}
void reciveMessageInternal(MessageProcessingSystem* target, char* message) {
	target->reciveMessage(json::parse((string)message));
}
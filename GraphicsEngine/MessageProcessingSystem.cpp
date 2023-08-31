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
	currentMessage = message;
	mtx.unlock();
}
json MessageProcessingSystem::getCurrentMessage() {
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
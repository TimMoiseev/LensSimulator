#include "pch.h"
#include "MessageProcessingSystem.h"

MessageProcessingSystem::MessageProcessingSystem()
{
}
void MessageProcessingSystem::destroyMessageProcessingSystem(MessageProcessingSystem* target)
{
	target->~MessageProcessingSystem();
}
void MessageProcessingSystem::reciveMessage(char* message){
	currentMessage = message;
}
string MessageProcessingSystem::getCurrentMessage() {
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
	target->reciveMessage(message);
}
#include "pch.h"
#include "MessageProcessingSystem.h"

MessageProcessingSystem::MessageProcessingSystem()
{
	//DoubleConvexLens = 0,
	//	PlanoConvexLens = 1,
	//	PositiveMeniscusLens = 2,
	//	NegativeMeniscusLens = 3,
	//	PlanoConcaveLens = 4,
	//	DoubleConcaveLens = 5
	lensTypeStringToEnum["DoubleConvexLens"] = OpticElementType::DoubleConvex;
	lensTypeStringToEnum["PlanoConvexLens"] = OpticElementType::PlanoConvex;
	lensTypeStringToEnum["PositiveMeniscusLens"] = OpticElementType::PositiveMeniscus;
	lensTypeStringToEnum["NegativeMeniscusLens"] = OpticElementType::NegativeMeniscus;
	lensTypeStringToEnum["PlanoConcaveLens"] = OpticElementType::PlanoConcave;
	lensTypeStringToEnum["DoubleConcaveLens"] = OpticElementType::DoubleConcave;
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

void MessageProcessingSystem::setResizeCallback(function<void(int, int)> f)
{
	resizeFunPointer = f;
}

void MessageProcessingSystem::setMouseWheelCallback(function<void(int)> f)
{
	mouseWheelPointer = f;
}

void MessageProcessingSystem::setChangeLensCallBack(function<void(string, int, float, float, float, float, float, float, float, OpticElementType)> f)
{
	changeLensFunPointer = f;
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
		else if (message["Type"].template get<std::string>() == "MouseWheel") {
			int z = message["zDelta"].template get<UINT>();
			if (z != 0) {
				mouseWheelPointer(z);
			}
			
		}
		else if (message["Type"].template get<std::string>() == "ChangeLensMessage") {
			string mt = message["MessageType"].template get<string>();
			OpticElementType type = lensTypeStringToEnum[message["LensType"].template get<string>()];
			int id = message["ID"].template get<int>();
			float d = message["D"].template get<float>();
			float r1 = message["R1"].template get<float>();
			float r2 = message["R2"].template get<float>();
			float h = message["H"].template get<float>();
			float x = message["X"].template get<float>();
			float y = message["Y"].template get<float>();
			float z = message["Z"].template get<float>();
			changeLensFunPointer(mt, id, d, r1, r2, h, x, y, z, type);
			
			
		}
	}
	
	return false;
}
json MessageProcessingSystem::getCurrentMessage() {
	mtx.lock();
	if (!messages.empty()) {
		currentMessage = messages.front();
		messages.pop();
	}
	else {
		currentMessage = nullptr;
	}
	mtx.unlock();
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
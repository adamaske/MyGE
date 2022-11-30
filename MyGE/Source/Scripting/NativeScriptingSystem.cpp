#include "NativeScriptingSystem.h"

void NativeScriptingSystem::Init()
{

	//We want to find every nativescriptcomponent
	auto scripts = Registry::Instance().GetComponents<NativeScriptComponent>();

	//We want to intatiate a subclass of ScriptableObject

	std::cout << "NativeScripting INIT" << std::endl;

	for (auto script : scripts) {
		script->mObject->Init();
	}

}

void NativeScriptingSystem::OnUpdate(float deltaTime)
{
	//We want to find every nativescriptcomponent
	auto scripts = Registry::Instance().GetComponents<NativeScriptComponent>();


	for (auto script : scripts) {
		script->mObject->OnUpdate(deltaTime);
	}
}

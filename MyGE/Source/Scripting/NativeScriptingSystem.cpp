#include "pch.h"
#include "NativeScriptingSystem.h"

void NativeScriptingSystem::Init()
{
	if (!Registry::Instance().Has<NativeScriptComponent>()) {
		Logger::Log("NativeSCriptingSystem : Registry has no components");
		return;
	}

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

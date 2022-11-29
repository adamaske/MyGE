#include "NativeScriptingSystem.h"

void NativeScriptingSystem::Init()
{

	//We want to find every nativescriptcomponent
	auto scripts = Registry::Instance().GetComponents<NativeScriptComponent>();

	for (auto script : scripts) {

	}

}

void NativeScriptingSystem::OnUpdate(float deltaTime)
{
	//We want to find every nativescriptcomponent
	auto scripts = Registry::Instance().GetComponents<NativeScriptComponent>();

	for (auto script : scripts) {

	}
}

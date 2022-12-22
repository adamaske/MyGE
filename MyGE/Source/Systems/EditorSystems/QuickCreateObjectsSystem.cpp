#include "pch.h"
#include "QuickCreateObjectsSystem.h"

void QuickCreateObjectSystem::Init() {

}

void QuickCreateObjectSystem::OnUpdate(float deltaTime) {
	if (Input::IsKeyDown(GLFW_KEY_I)) {
		Logger::Log("QuickCreateObjectSystem : CREATE A OBJECT!");
	}
	
}
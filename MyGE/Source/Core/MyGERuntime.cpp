#include "pch.h"
#include "MyGERuntime.h"
#include "MyGEEditor.h"
#include "MyGEMode.h"
#include "../Scenes/Scene.h"

MyGERuntime::MyGERuntime()
{
}

void MyGERuntime::Init()
{

	//Create systems which the runtime uses, or init different settings, 
}

void MyGERuntime::OnUpdate(float deltaTime)
{
	if (bRunning) {
		//mScene->OnUpdate(deltaTime);
		//
		//for (auto system : mSystems) {
		//	system->OnUpdate(deltaTime);
		//}
	}
}

void MyGERuntime::StartRuntime(std::shared_ptr<Scene> scene)
{
	mScene = scene;

	bRunning = true;
}

void MyGERuntime::StopRuntime()
{
	bRunning = false;
}

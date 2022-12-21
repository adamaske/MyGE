#include "pch.h"
#include "MyGERuntime.h"

#include "MyGEMode.h"
#include "../Scenes/Scene.h"

MyGERuntime::MyGERuntime()
{
}

void MyGERuntime::Init()
{
}

void MyGERuntime::OnUpdate(float deltaTime)
{
}

void MyGERuntime::StartRuntime(std::shared_ptr<Scene> scene)
{
	mScene = scene;
}

void MyGERuntime::StopRuntime()
{
}

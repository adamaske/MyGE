#include "pch.h"
#include "MyGEEditor.h"
#include "MyGERuntime.h"
#include "MyGEMode.h"
#include "../Scenes/Scene.h"
void MyGEEditor::Init()
{
}

void MyGEEditor::OnUpdate(float deltaTime)
{
}

bool MyGEEditor::LoadScene(std::string fileName)
{
	return false;
}

void MyGEEditor::StartPlay()
{
	//auto serializedScene = SerializeScene(GetScene())
	//mRuntime->StartRuntime(serializedScene);
	mRuntime->StartRuntime(GetScene());

}

void MyGEEditor::StopPlay()
{
	mRuntime->StopRuntime();
}

std::shared_ptr<Scene> MyGEEditor::GetScene()
{
	return std::shared_ptr<Scene>();
}

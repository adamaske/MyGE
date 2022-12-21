#include "pch.h"
#include "MyGEEditor.h"
#include "MyGERuntime.h"
#include "MyGEMode.h"

#include "../Scenes/Scene.h"
#include "../Systems/System.h"
#include "../Systems/EditorSystems/QuickCreateObjectsSystem.h"

void MyGEEditor::Init()
{
	//The systems which the Scene use should go in here instead

}

void MyGEEditor::OnUpdate(float deltaTime)
{
	//What should be systems in the scene, what
	
}

bool MyGEEditor::LoadScene(std::string fileName)
{
	
	//auto scene = SceneLoader::Load(fileName);
	return false;
}

bool MyGEEditor::LoadScene(std::shared_ptr<Scene> scene)
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

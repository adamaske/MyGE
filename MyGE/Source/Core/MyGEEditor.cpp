#include "pch.h"
#include "MyGEEditor.h"
#include "MyGERuntime.h"
#include "MyGEMode.h"

#include "../RenderWindow.h"

#include "../Scenes/Scene.h"
#include "../Scenes/MonkeyScene.h"

#include "../ShaderManager.h"

#include "../Systems/System.h"
#include "../Systems/CameraSystem.h"
#include "../Systems/RenderSystem.h"
#include "../Systems/TerrainSystem.h"
#include "../Scripting/NativeScriptingSystem.h"
//Editor systems
#include "../Systems/EditorSystems/QuickCreateObjectsSystem.h"
//#include "../Systems/EditorSystems/SceneViewSystem.h"
//#include "../Systems/EditorSystems/GameViewSystem.h"

#include "../Cameras/Camera.h"
#include "../Cameras/CameraMovement.h"
//#include "../Cameras/EditorCamera.h"

#include "../Textures/Texture.h"
#include "../Textures/TextureManager.h"
void MyGEEditor::Init()
{	
	mActiveScene = std::make_shared<MonkeyScene>();
	mActiveScene->Init();

	//The systems which the Scene use should go in here instead
	//Creates registry for this scene



	

#pragma region Systems

	//Creating systems
	mSystems.insert({ "RenderSystem", new RenderSystem() });
	mSystems.insert({ "TerrainSystem", new TerrainSystem() });
	mSystems.insert({ "CameraSystem" , new CameraSystem() });
	//OPENAL32.DLL NOT FOUND CAUSES THIS TO ERROR ->>> 
	//mSystems.insert({ "AudioSystem", new AudioSystem() });
	mSystems.insert({ "NativeScriptingSystem", new NativeScriptingSystem() });

	//Init all systems
	for (auto system : mSystems)
	{
		//Creating systems
		Logger::Log("Starting init for system : " + (std::string)system.first);
		system.second->Init();
	}
	Logger::Log("Finished creating Initing systems");
#pragma endregion
}

void MyGEEditor::OnUpdate(float deltaTime)
{

	for (auto system : mSystems)
	{
		system.second->OnUpdate(deltaTime);
	}
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

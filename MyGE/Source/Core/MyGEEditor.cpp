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
#include "../Systems/EditorSystems/SceneViewSystem.h"

#include "../Cameras/Camera.h"
void MyGEEditor::Init()
{
	//The systems which the Scene use should go in here instead

	//We want to load the startup scene
	//Swap make shared for call to scenemanager->GetScene(mStartupScene)
	//LoadScene(mSceneManager->GetScene(mStartupScene));
	
#pragma region Viewports
	mGameViewport = std::make_shared<RenderWindow>();
	mGameViewport->Init(glfwCreateWindow(500, 500, "Game", NULL, NULL));
	mGameViewport->Hide();

	mSceneViewport = std::make_shared<RenderWindow>();
	mSceneViewport->Init(glfwCreateWindow(1200, 800, "Scene", NULL, NULL));
	mSceneViewport->MakeCurrent();


#pragma endregion

	mActiveScene = std::make_shared<MonkeyScene>();
	if (!LoadScene(mActiveScene)) {
		Logger::Log("MyGEEditor : Could not load scene!", ERROR);
	}
	mActiveScene->Init();
	
	mEditorCamera = std::make_shared<Camera>();
	//mEditorCamera = std::make_shared<Camera>();
#pragma region Create Systems
	//todo : Move into own function, remove duplicate code between this and runtime
	// What systems does the editor need
	// Different performance modes may use differnet systems etc :D
	//Creating system
	mSystems.insert({ "RenderSystem", std::make_shared<RenderSystem>()});
	mSystems.insert({ "TerrainSystem", std::make_shared<TerrainSystem>() });
	//mSystems.insert({ "CameraSystem" , std::make_shared<CameraSystem>() });
	//OPENAL32.DLL NOT FOUND CAUSES THIS TO ERROR ->>> 
	//mSystems.insert({ "AudioSystem", new AudioSystem() });
	mSystems.insert({ "NativeScripting", std::make_shared<NativeScriptingSystem>() });

	//Editor systems
	mSystems.insert({"QuickCreateObject", std::make_shared<QuickCreateObjectSystem>()});
	mSystems.insert({ "SceneView", std::make_shared<SceneViewSystem>() });
	//Init all systems
	for (auto system : mSystems)
	{
		//Creating systems
		Logger::Log("Starting init for system : " + (std::string)system.first);
		system.second->Init();
	}
#pragma endregion

	
}

void MyGEEditor::OnUpdate(float deltaTime)
{
	if (mSceneViewport->Focused()) {
		//Do scene rendering
		//We may want different stuff showing in the scene viewport
		auto shaders = ShaderManager::Instance()->GetShaders();
		//Apply editorcamera to all shaders
		for (auto shader : shaders) {
			shader->SetUniformMatrix4(mEditorCamera->GetViewMatrix(), "vMatrix");
			shader->SetUniformMatrix4(mEditorCamera->GetProjectionMatrix(), "pMatrix");
		}
		//Then we render the scene? 
		//todo : need to 
	}
	if (mGameViewport->Focused()) {
		//
	}
	//What should be systems in the scene, what
	//Maybe it should be a vector instead, we iterate through it every frame
	for (auto system : mSystems) {
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
	//mActiveScene = scene;
	return true;
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


void MyGEEditor::ViewportRezised(int width, int height) {
	//mViewportWidth = width;
	//mViewportHeight = height;
	//GO through all cameras and change their aspect ratio and size 
	auto cameras = Registry::Instance().GetComponents<CameraComponent>();
	for (auto& cam : cameras)
	{
		//Change cameras without a fixed ar
		if (!cam->bFixedAsceptRatio) {
			//Remove one of these
			cam->mCamera->SetViewportSize(width, height);

			cam->mAspectRatio = ((float)width / (float)height);

		}
	}
}
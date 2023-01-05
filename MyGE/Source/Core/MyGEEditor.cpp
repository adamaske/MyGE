#include "pch.h"
#include "MyGEEditor.h"
#include "MyGERuntime.h"
#include "MyGEMode.h"

#include "../RenderWindow.h"

#include "../Scenes/Scene.h"
#include "../Scenes/MonkeyScene.h"

#include "../Shaders/Shader.h"
#include "../Shaders/ShaderManager.h"

#include "../Systems/System.h"
#include "../Systems/CameraSystem.h"
#include "../Systems/RenderSystem.h"
#include "../Systems/TerrainSystem.h"
#include "../Scripting/NativeScriptingSystem.h"
//Editor systems
#include "../Systems/EditorSystems/QuickCreateObjectsSystem.h"

#include "../Cameras/Camera.h"
#include "../Cameras/EditorCamera.h"

void MyGEEditor::Init()
{
	//The systems which the Scene use should go in here instead

	//We want to load the startup scene
	//Swap make shared for call to scenemanager->GetScene(mStartupScene)
	//LoadScene(mSceneManager->GetScene(mStartupScene));
	
#pragma region Viewports
	// mGameViewport = std::make_shared<RenderWindow>();
	// mGameViewport->Init(glfwCreateWindow(500, 500, "Game", NULL, NULL));
#pragma endregion

	mActiveScene = std::make_shared<MonkeyScene>();
	if (!LoadScene(mActiveScene)) {
		Logger::Log("MyGEEditor : Could not load scene!", ERROR);
	}
	mActiveScene->Init();
	

	mEditorCamera = std::make_shared<EditorCamera>();
	mEditorCamera->mOldX = 0;
	mEditorCamera->mOldY = 0;

	//mEditorCamera = std::make_shared<Camera>();


#pragma region Systems
	//todo : Move into own function, remove duplicate code between this and runtime

	mSystems.insert({ "RenderSystem", std::make_shared<RenderSystem>() });
	mSystems.insert({ "TerrainSystem", std::make_shared<TerrainSystem>() });

	//The Camera system is for when the scene is rendered and should probably go into the scene systems
	//mSystems.insert({ "CameraSystem" , std::make_shared<CameraSystem>() });
	mSystems.insert({ "NativeScripting", std::make_shared<NativeScriptingSystem>() });
	//OPENAL32.DLL NOT FOUND CAUSES THIS TO ERROR ->>> 
	//mSystems.insert({ "AudioSystem", new AudioSystem() });

	//Editor systems
	//mSystems.insert({"QuickCreateObject", std::make_shared<QuickCreateObjectSystem>()});
	//This deals with everything -> displaying the scene
	//mSystems.insert({ "SceneView", std::make_shared<SceneViewSystem>() });
	//mSystems.insert({ "GameView", std::make_shared<GameViewSystem>() });
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
	//TODO put all this in a system or a function
	//apply changes to editor camera
#pragma region EditorCamera
	//Set mouse pos to 0,0
	

	//Do rotation before movement to have updated vectors
#pragma region Rotation
	//Left mouse, rotate when this is down
	//Not working yet so it wont run
	if (Input::IsMouseButtonDown(GLFW_MOUSE_BUTTON_2)) {
		//We want the mosue to be at 0,0 when doing this
		if (mEditorCamera->bMousePressed) {
			std::cout << "PRESSED!" << std::endl;
			mEditorCamera->bMousePressed = false;
		}
		float x = Input::MouseX();
		float y = Input::MouseY();
		glfwSetCursorPos(glfwGetCurrentContext(), 600, 400);

		float dX = Input::DeltaMouseX();
		float dY = Input::DeltaMouseY();
		//Logger::Log("MOUSEBUTTON 2 DOWN");
		//
		////find the delta
		//Ignoring this for now
		
		//this is enough for now
		
		//how to caluclate this?? we want to update both 
		//mForward, mRight and mUp based on the target location
	}
	
	
#pragma endregion

#pragma region Movement
	if (Input::IsKeyDown(GLFW_KEY_W)){
		mEditorCamera->mPosition += mEditorCamera->mForward * mEditorCamera->mMoveSpeed * deltaTime;
	}
	//apply changes to editor camera
	if (Input::IsKeyDown(GLFW_KEY_S)) {
		mEditorCamera->mPosition += -mEditorCamera->mForward * mEditorCamera->mMoveSpeed * deltaTime;
	}
	//apply changes to editor camera
	if (Input::IsKeyDown(GLFW_KEY_A)) {
		mEditorCamera->mPosition += mEditorCamera->mRight * mEditorCamera->mMoveSpeed * deltaTime;
	}
	//apply changes to editor camera
	if (Input::IsKeyDown(GLFW_KEY_D)) {
		mEditorCamera->mPosition += -mEditorCamera->mRight * mEditorCamera->mMoveSpeed * deltaTime;
	}
#pragma endregion

	//Rotaiton
	// 
	// //Set p and v matrices
	mEditorCamera->mViewMatrix = glm::lookAt(mEditorCamera->mPosition, mEditorCamera->mPosition + mEditorCamera->mTargetOffset, glm::vec3(0, 1, 0));	//add near and far to camera
	//cam->mViewMatrix = glm::lookAt(glm::vec3(0, -3), pos + glm::vec3(0, 0, 1), glm::vec3(0, 1, 0));
	mEditorCamera->mProjectionMatrix = glm::perspective(glm::radians(mEditorCamera->mFOV), mEditorCamera->mAspectRatio, 0.1f, 1000.f);

	//Apply to the shaders
	auto shaders = ShaderManager::Instance()->GetShaders();
	for (auto shader : shaders) {
		//Use this shader
		shader->Use();
		//Set the variables in the shaders, I currently dont know any scenario where this changes
		shader->SetUniformMatrix4(mEditorCamera->mViewMatrix, "vMatrix");
		shader->SetUniformMatrix4(mEditorCamera->mProjectionMatrix, "pMatrix");

	}

#pragma endregion

	//Maybe it should be a vector instead, we iterate through it every frame
	for (auto system : mSystems) {
		system.second->OnUpdate(deltaTime);
	}
	//mActiveScene->OnUpdate(deltaTime);
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
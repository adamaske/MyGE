#include "pch.h"
#include "SceneViewSystem.h"

#include "../../RenderWindow.h"

#include "../../Cameras/EditorCamera.h"

#include "../../ShaderManager.h"
SceneViewSystem::SceneViewSystem()
{
}

void SceneViewSystem::Init()
{
	mSceneViewport = std::make_shared<RenderWindow>();
	mSceneViewport->Init(glfwCreateWindow(1200, 800, "Scene", NULL, NULL));
	mSceneViewport->MakeCurrent();
	glfwSetWindowUserPointer(mSceneViewport->GetWindow(), reinterpret_cast<void*>(this));
	glfwSetWindowSizeCallback(mSceneViewport->GetWindow(), FramebufferResizedCallback);
	mEditorCamera = std::make_shared<EditorCamera>();
}

void SceneViewSystem::OnUpdate(float deltaTime)
{
	//These can be put into their own systems
	//These should be totally independent to eachother
	if (!mSceneViewport->IsHidden()) {
		//Do scene rendering
		mEditorCamera->OnUpdate(deltaTime);
		//We may want different stuff showing in the scene viewport
		auto shaders = ShaderManager::Instance()->GetShaders();
		//Apply editorcamera to all shaders
		auto shader = ShaderManager::Instance()->GetShader("MyGEShader");
		shader->Use();
		auto v = mEditorCamera->GetViewMatrix();
		auto p = mEditorCamera->GetProjectionMatrix();
		shader->SetUniformMatrix4(v, "vMatrix");
		shader->SetUniformMatrix4(p, "pMatrix");
		
		//Then we render the scene? 
		//todo : need to 
		//Render everything
	}
}

void SceneViewSystem::FramebufferResizedImplementation(int width, int height)
{
	mEditorCamera->SetViewportSize(width, height);
}

void SceneViewSystem::FramebufferResizedCallback(GLFWwindow* window, int width, int height)
{
	SceneViewSystem* handler = reinterpret_cast<SceneViewSystem*>(glfwGetWindowUserPointer(window));
	if (handler) {
		handler->FramebufferResizedImplementation(width, height);
	}
}

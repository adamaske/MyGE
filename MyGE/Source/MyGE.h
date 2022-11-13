#pragma once
//#include "glew.h"
#include <vector>



//All includes, everything include this
#include "Components.h"
#include "GameObject.h"

#include "Registry.h"

#include "MainWindow.h"
#include "RenderWindow.h"

#include "Scene.h"
#include "../../MyGE/Source/SceneManager.h"

#include "Script.h"
#include "ScriptingManager.h"

#include "Shader.h"
#include "ShaderManager.h"



class MyGE
{
public:

	MyGE();

	int run();

	void ProcessInput();

	void ResizeWindow(uint32_t width, uint32_t height);

	void CalculateDeltaTime();
protected:
	RenderWindow* mWindow;

	////Lua scripting
	ScriptingManager* mScriptingManager;
	//Scene manager
	SceneManager* mSceneManager;

	class ShaderManager* mShaderManager;

	Scene* mScene;

	RenderWindow* mRenderWindow;
	float mWindowHeight = 1200;
	float mWindowWidth = 900;
	//Keeping track of deltaTime
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	static void WindowSizeChangedCallback(GLFWwindow* window, int width, int height) {
		//This window pointer is associated width his MYGE instance
		MyGE* obj = reinterpret_cast<MyGE*>(glfwGetWindowUserPointer(window));
		obj->ResizeWindow(width, height);
	};

};

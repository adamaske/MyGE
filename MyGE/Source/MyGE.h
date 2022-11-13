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


protected:
	RenderWindow* mWindow;

	////Lua scripting
	ScriptingManager* mScriptingManager;
	//Scene manager
	SceneManager* mSceneManager;

	class ShaderManager* mShaderManager;

	Scene* mScene;

	GLFWwindow* mRenderWindow;

	bool mFirstClick = false;
	float mWindowHeight = 1200;
	float mWindowWidth = 900;
	float mMouseSensitivity = 0.1f;
	glm::quat mOrientation;
};

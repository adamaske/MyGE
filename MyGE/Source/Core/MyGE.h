#pragma once

class MyGE
{
public:

	MyGE();

	int Run();

	void ProcessInput();

	void ResizeWindow(uint32_t width, uint32_t height);

	void CalculateDeltaTime();

	void ExitApplication();
protected:
	class RenderWindow* mWindow;

	//Are these managers nessacery, should they be systems instead?
	// 
	////Lua scripting
	class ScriptingManager* mScriptingManager;
	
	class SceneManager *mSceneManager;

	class ShaderManager* mShaderManager;

	class TextureManager* mTextureManger;
	
	class Scene* mScene;
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

	bool bRuntime = true;

	std::shared_ptr<class MyGEMode> mActiveMode;
	std::shared_ptr<class MyGEEditor> mEditor;
	std::shared_ptr<class MyGERuntime> mRuntime;

	bool bRunning = true;
};


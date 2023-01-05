#pragma once

class MyGE
{
public:

	MyGE();

	int Run();

	void ResizeWindow(uint32_t width, uint32_t height);

	void CalculateDeltaTime();

	void ExitApplication();
protected:
	std::shared_ptr<class RenderWindow> mRenderWindow;

	//Are these managers nessacery, should they be systems instead?
	// Could be uniqe pointers instead, should these managers exist at all?
	////Lua scripting
	std::shared_ptr<class ScriptingManager> mScriptingManager;
	//Scene manager
	std::shared_ptr<class SceneManager>mSceneManager;

	std::shared_ptr<class ShaderManager> mShaderManager;

	std::shared_ptr<class TextureManager> mTextureManager;
	
	//Keeping track of deltaTime
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;
	float mDeltaTime = 0.f;

	static void WindowSizeChangedCallback(GLFWwindow* window, int width, int height) {
		//This window pointer is associated width his MYGE instance
		MyGE* obj = reinterpret_cast<MyGE*>(glfwGetWindowUserPointer(window));
		obj->ResizeWindow(width, height);
	};

	bool bRuntime = false;

	std::shared_ptr<class MyGEMode> mActiveMode;
	std::shared_ptr<class MyGEEditor> mEditor;
	std::shared_ptr<class MyGERuntime> mRuntime;

	bool bRunning = true;
};


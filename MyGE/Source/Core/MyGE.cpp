#include "pch.h"

#include "MyGE.h"
#include "MyGEMode.h"
#include "MyGEEditor.h"
#include "MyGERuntime.h"

#include "../Textures/Texture.h"
#include "../Textures/TextureManager.h"

#include "../Components/Components.h"

#include "../MainWindow.h"
#include "../RenderWindow.h"

#include "../Scenes/Scene.h"
#include "../Scenes/SceneManager.h"

#include "../Script.h"
#include "../Scripting/ScriptingManager.h"

#include "../Shader.h"
#include "../ShaderManager.h"



void glfw_onError(int error, const char* desc) {
	std::cout << "GLFW error : " << error << ", " << desc << std::endl;
}

MyGE::MyGE() {
	mWindowWidth = 1280;
	mWindowHeight = 720;

}
int MyGE::Run()
{
	std::cout << "MyGE : started running" << std::endl;
	Logger::Init();
	//Init gl
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);


	//Our window into the game world is a RenderWindow
	//Init, close if not sucess
	mRenderWindow = new RenderWindow();
	mRenderWindow->Init(glfwCreateWindow(mWindowWidth, mWindowHeight, "MyGE", NULL, NULL));
	//The renderwindow's window has a pointer to this MyGE object,
	//Should be changed to a Editor later
	//vsync
	glfwSwapInterval(1);
	//Loading glad?
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		Logger::Log("Failed to initialize GLAD", ERROR, true);
		return -1;
	}

	glEnable(GL_DEPTH_TEST);
	
	//Scene Manager 
	mSceneManager = new SceneManager();
	//Scripting manager to handle all lua and native scripting
	mScriptingManager = new ScriptingManager();
	//A shader manager to store all shaders
	ShaderManager::Instance();
	
	mTextureManger = new TextureManager();
	mTextureManger->InsertTexture("../Resources/Textures/hammerDiffuse.bmp", "HammerDiffuse");

	//
	mScene = new Scene();
	//mSceneManager->AddScene(*mScene);
	mScene->Init();
	
	//resize window immediatly 
	ResizeWindow(1200, 800);
	// Time between current frame and last frame
	// Time of last frame
	//mEditor->LoadScene("../Resources/Scenes/MonkeyScene.ge");
	//mEditor->Init();
	bool bEditorMode = true;
	if (bEditorMode) {
		//We want to launch the editor
	}
	else {
		//we want only the runtime, 
		//This may require totally different systems
	}
	//we want the editor to load
	mEditor = std::make_shared<MyGEEditor>();
	//Sets the active mode to this
	mActiveMode = mEditor;
	
	//In the future we want to generlize this, 
	//with more runtimes which uses the same game engine etc, 
	//we can have high performance testing and maybe multiplayer testing
	//It can also be made into a different project
	mRuntime = std::make_shared<MyGERuntime>();

	while (bRunning)
	{
		//Get events
		glfwPollEvents();

		CalculateDeltaTime();
		
		//Process input
		ProcessInput();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		//Update scene
		mEditor->OnUpdate(deltaTime);
		//Rendering
		mRenderWindow->Render(deltaTime);

		//
		glfwSwapBuffers(mRenderWindow->GetWindow());
	}
	//Do cleanup here
	glfwTerminate();

	return 0;
}
    

void MyGE::ProcessInput()
{
    if (glfwGetKey(mRenderWindow->GetWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        
        glfwSetWindowShouldClose(mRenderWindow->GetWindow(), true);
    } 

	if (glfwGetKey(mRenderWindow->GetWindow(), GLFW_KEY_P) == GLFW_PRESS) {
		//mRuntime->Play();
	}
}

void mouse_callback(GLFWwindow * window, double xposIn, double yposIn)
{
	MyGE* obj = reinterpret_cast<MyGE*>(glfwGetWindowUserPointer(window));

};

void MyGE::ResizeWindow(uint32_t width, uint32_t height) {

	//Tell the scene that the veiwport is changed
	mScene->ViewportRezised(width, height);
	glViewport(0, 0, width, height);
}

void MyGE::CalculateDeltaTime()
{
	//Calculate deltatime
	float currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
}

void MyGE::ExitApplication()
{
	bRunning = false;
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	
}
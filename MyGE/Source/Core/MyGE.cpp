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


#include "../Logger.h"

void glfw_onError(int error, const char* desc) {
	std::cout << "GLFW error : " << error << ", " << desc << std::endl;
}

MyGE::MyGE() {
}
int MyGE::Run()
{
	Logger::Init();
	Logger::Log("MyGE : started running");
	//Init gl
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	
	glfwMakeContextCurrent(glfwCreateWindow(100, 100, "MyGE", NULL, NULL));
	//vsync
	glfwSwapInterval(1);

	//Loading glad?
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		Logger::Log("Failed to initialize GLAD", LogType::ERROR, true);
		return -1;
	}
	glfwDestroyWindow(glfwGetCurrentContext());
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_TEXTURE_2D);
	//Scene Manager 
	mSceneManager = std::make_shared<SceneManager>();
	//Scripting manager to handle all lua and native scripting
	mScriptingManager = std::make_shared<ScriptingManager>();
	//A shader manager to store all shaders
	ShaderManager::Instance();
	mTextureManger = std::make_shared<TextureManager>();
	mTextureManger->InsertTexture("../Resources/Textures/hammerDiffuse.bmp", "HammerDiffuse");

	//Here we can parse arguments wheter we launch the editor or runtime for example
	//if args++ == -e Launch editor, == -r Launch runtime

	//This must happend before glad loading
	//we want the editor to load
	mActiveMode = mEditor = std::make_shared<MyGEEditor>();
	mEditor->Init();


	//In the future we want to generlize this, 
	//with more runtimes which uses the same game engine etc, 
	//we can have high performance testing and maybe multiplayer testing
	//It can also be made into a different project
	mRuntime = std::make_shared<MyGERuntime>();
	
	bool bEditorMode = true;
	if (bEditorMode) {
		//We want to launch the editor
	}
	else {
		//we want only the runtime, 
		//This may require totally different systems
	}

	//resize window immediatly 
	ResizeWindow(1200, 800);

	
	while (bRunning)
	{
		//Get events
		glfwPollEvents();

		if (Input::IsKeyDown(GLFW_KEY_ESCAPE)) {
			ExitApplication();
		}

		CalculateDeltaTime();
		

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		//Update editor
		mEditor->OnUpdate(deltaTime);
		//Rendering
		//Renderer->Render(); Should have a queue, so all the opengl code here can go into there
		//
		glfwSwapBuffers(glfwGetCurrentContext());
	}
	//Do cleanup here
	glfwTerminate();

	return 0;
}
    

void mouse_callback(GLFWwindow * window, double xposIn, double yposIn)
{
	MyGE* obj = reinterpret_cast<MyGE*>(glfwGetWindowUserPointer(window));

};

void MyGE::ResizeWindow(uint32_t width, uint32_t height) {

	//Tell the scene that the veiwport is changed
	//mScene->ViewportRezised(width, height);
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
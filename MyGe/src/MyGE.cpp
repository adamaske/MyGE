#include "MyGE.h"
#include <iostream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "MainWindow.h"
#include "RenderWindow.h"
#include "Scene.h"

#include "Shader.h"

void glfw_onError(int error, const char* desc) {
	std::cout << "GLFW error : " << error << ", " << desc << std::endl;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
MyGE::MyGE() {

}
int MyGE::run()
{
	std::cout << "MyGE : started running" << std::endl;
	//// define the function's prototype
	//typedef void (*GL_GENBUFFERS) (GLsizei, GLuint*);
	//// find the function and assign it to a function pointer
	//GL_GENBUFFERS glGenBuffers = (GL_GENBUFFERS)glfwGetProcAddress("glGenBuffers");
	//// function can now be called as normal
	//unsigned int buffer;
	//glGenBuffers(1, &buffer);
	//Init gl
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	//Our window into the game world is a RenderWindow
	//mWindow = RenderWindow();
	//Init, close if not sucess
	GLFWwindow* window = glfwCreateWindow(800, 600, "MyGE", NULL, NULL);
	//mWindow.Init(window);
	if (window == NULL) {
		std::cout << "MyGE : Failed to create GLFW Window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, 800, 600);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	mWindow = new RenderWindow();

	//In this demo I will render 1 secen
	Registry* registry = new Registry();
	std::cout << "MyGE : " << std::endl;
	//Scene Manager created
	mSceneManager = new SceneManager();

	mScriptingManager = new ScriptingManager();

	//Creates registry instance
	Registry::Instance();

	mScene = new Scene(*mShaderManager);
	mScene->Init();

 	while (!glfwWindowShouldClose(window))
	{
		//Process input
		ProcessInput();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}



	//mSceneManager = *scenemanager;
	//Scene* scene = new Scene(*registry, mShaderManager);
	//mSceneManager.AddScene(*scene);
	////The render window knows what scene to render
	////mWindow->SetActiveScene(scene);
	//
	////Creates registry instance
	//Registry::Instance();
	//
	//ScriptingManager scripting = ScriptingManager();
	//mScriptingManager = scripting;
	//mScriptingManager.Init();
	//
	////Init
	//mSceneManager.GetScene().Init(mShaderManager);
	//The render window knows what scene to render
	//mWindow->SetActiveScene(mSceneManager->GetScene());
	//Main loop
	//while (!mWindow.ShouldCloseWindow()) {
	//    glfwSwapBuffers(window);
	//    glfwPollEvents();
	//   // std::cout << "MyGE : While loop" << std::endl;
	//   // double time = glfwGetTime();
	//   // //Process input
	//   // ProcessInput();
	//   // //Change Game
	//   // mSceneManager.GetScene().OnUpdate();
	//   // 
	//   // //Render
	//   // mWindow.Render();
	//}
	glfwTerminate();

	return 0;
}

void MyGE::ProcessInput()
{
	//if (glfwGetKey(mWindow.GetWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS) {
	//    std::cout << "Escape Pressed" << std::endl;
	//    glfwSetWindowShouldClose(mWindow.GetWindow(), true);
	//}
	//if (glfwGetKey(mWindow.GetWindow(), GLFW_KEY_W) == GLFW_PRESS) {
	//    std::cout << "Move forward" << std::endl;
	//  
	//}
	//if (glfwGetKey(mWindow.GetWindow(), GLFW_KEY_N) == GLFW_PRESS) {
	//    std::cout << "Move forward" << std::endl;
	//    //Launches new scene
	//    Scene& s = mSceneManager.GetNextScene(1);
	//    //Init the scene
	//    s.Init(mShaderManager);
	//    //The render window knows what scene to render
	//    //mWindow->SetActiveScene(s);
	//}
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

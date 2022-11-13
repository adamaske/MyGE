#include "MyGE.h"
#include "MainWindow.h"
#include "RenderWindow.h"
#include "Scene.h"
#include "Shader.h"

#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtx/quaternion.hpp"

void glfw_onError(int error, const char* desc) {
	std::cout << "GLFW error : " << error << ", " << desc << std::endl;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
MyGE::MyGE() {
 
}
int MyGE::run()
{
	std::cout << "MyGE : started running" << std::endl;
	// define the function's prototype
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
	mRenderWindow = glfwCreateWindow(1200, 800, "MyGE", NULL, NULL);
	//glViewport(0, 0, 1200, 800);
	//mWindow.Init(window);
	if (mRenderWindow == NULL) {
		std::cout << "MyGE : Failed to create GLFW Window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(mRenderWindow);
	glfwSwapInterval(1);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	//GLenum err = glewInit();
	//if (GLEW_OK != err)
	//{
	//	/* Problem: glewInit failed, something is seriously wrong. */
	//	std::cerr << "Error: " << glewGetErrorString(err) << std::endl;
	//
	//}
	//std::cerr << "Status: Using GLEW " << glewGetString(GLEW_VERSION) << std::endl;


	glfwSetFramebufferSizeCallback(mRenderWindow, framebuffer_size_callback);
	glViewport(0, 0, 1200, 800);
	glEnable(GL_DEPTH_TEST);
	//In this demo I will render 1 secen
	Registry* registry = new Registry();
	std::cout << "MyGE : " << std::endl;
	//Scene Manager created|
	mSceneManager = new SceneManager();

	mScriptingManager = new ScriptingManager();

	mShaderManager = new ShaderManager();
	//Creates registry instance
	Registry::Instance();

	mScene = new Scene(*mShaderManager);
	mScene->Init();

	while (!glfwWindowShouldClose(mRenderWindow))
	{
		//Process input
		ProcessInput();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Draw our first triangle
		glUseProgram(mShaderManager->GetShader("PlainShader")->GetProgram());
		//Rendering

		//Update game
		mScene->OnUpdate(1.0f/60.f);


		glfwSwapBuffers(mRenderWindow);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}
    

void MyGE::ProcessInput()
{
    if (glfwGetKey(mRenderWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        std::cout << "Escape Pressed" << std::endl;
        glfwSetWindowShouldClose(mRenderWindow, true);
    }
    if (glfwGetKey(mRenderWindow, GLFW_KEY_W) == GLFW_PRESS) {
        std::cout << "Move forward" << std::endl;
      
    }

	if (glfwGetKey(mRenderWindow, GLFW_KEY_W) == GLFW_PRESS) {
		auto camera = Registry::Instance().GetComponents <CameraComponent>();
		for (int i = 0; i < camera.size(); i++) {
			if (camera[i]->bIsMainCamera) {

				auto& transform = Registry::Instance().GetComponent<TransformComponent>(camera[i]->mGameObjectID);
				transform.mMatrix[3].z += 1 / 60.f;
			}
		}
	}

	if (glfwGetKey(mRenderWindow, GLFW_KEY_S) == GLFW_PRESS) {
		auto camera = Registry::Instance().GetComponents <CameraComponent>();
		for (int i = 0; i < camera.size(); i++) {
			if (camera[i]->bIsMainCamera) {

				auto& transform = Registry::Instance().GetComponent<TransformComponent>(camera[i]->mGameObjectID);
				transform.mMatrix[3].z -= 1 / 60.f;
			}
		}
	}

	if (glfwGetKey(mRenderWindow, GLFW_KEY_A) == GLFW_PRESS) {
		auto camera = Registry::Instance().GetComponents <CameraComponent>();
		for (int i = 0; i < camera.size(); i++) {
			if (camera[i]->bIsMainCamera) {

				auto& transform = Registry::Instance().GetComponent<TransformComponent>(camera[i]->mGameObjectID);
				transform.mMatrix[3].x += 1 / 60.f;
			}
		}
	}

	if (glfwGetKey(mRenderWindow, GLFW_KEY_D) == GLFW_PRESS) {
		auto camera = Registry::Instance().GetComponents <CameraComponent>();
		for (int i = 0; i < camera.size(); i++) {
			if (camera[i]->bIsMainCamera) {

				auto& transform = Registry::Instance().GetComponent<TransformComponent>(camera[i]->mGameObjectID);
				transform.mMatrix[3].x -= 1 / 60.f;
			}
		}
	}
    // Handles mouse inputs
	if (glfwGetMouseButton(mRenderWindow, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		// Hides mouse cursor
		glfwSetInputMode(mRenderWindow, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    
		// Prevents camera from jumping on the first click
		if (mFirstClick)
		{
			glfwSetCursorPos(mRenderWindow, (mWindowWidth / 2), (mWindowHeight / 2));
			mFirstClick = false;
		}
    
		// Stores the coordinates of the cursor
		double mouseX;
		double mouseY;
		// Fetches the coordinates of the cursor
		glfwGetCursorPos(mRenderWindow, &mouseX, &mouseY);
    
		// Normalizes and shifts the coordinates of the cursor such that they begin in the middle of the screen
		// and then "transforms" them into degrees 
		float rotX = mMouseSensitivity * (float)(mouseY - (mWindowHeight / 2)) / mWindowHeight;
		float rotY = mMouseSensitivity * (float)(mouseX - (mWindowWidth / 2)) / mWindowWidth;
    
		//// Calculates upcoming vertical change in the Orientation
		//glm::vec3 newOrientation = glm::rotate(mOrientation, glm::radians(-rotX), glm::normalize(glm::cross(mOrientation, glm::quat(1))));
    	//
		//// Decides whether or not the next vertical Orientation is legal or not
		//if (abs(glm::angle(newOrientation, Up) - glm::radians(90.0f)) <= glm::radians(85.0f))
		//{
		//	Orientation = newOrientation;
		//}
		// Rotates the Orientation left and right
		mOrientation = glm::rotate(mOrientation, glm::radians(-rotY), glm::vec3(0,1,0));
	
		
		// Sets mouse cursor to the middle of the screen so that it doesn't end up roaming around
		glfwSetCursorPos(mRenderWindow, (mWindowWidth / 2), (mWindowHeight / 2));
	}
	else if (glfwGetMouseButton(mRenderWindow, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
	{
		// Unhides cursor since camera is not looking around anymore
		glfwSetInputMode(mRenderWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		// Makes sure the next time the camera looks around it doesn't jump
		mFirstClick = true;
	}
}
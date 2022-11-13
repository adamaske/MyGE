#include "MyGE.h"
#include "MainWindow.h"
#include "RenderWindow.h"
#include "Scene.h"
#include "Shader.h"
#include "Systems/System.h"

#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtx/quaternion.hpp"


void glfw_onError(int error, const char* desc) {
	std::cout << "GLFW error : " << error << ", " << desc << std::endl;
}
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

MyGE::MyGE() {
	mWindowWidth = 1280;
	mWindowHeight = 720;
}
int MyGE::run()
{
	std::cout << "MyGE : started running" << std::endl;

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
	glfwSetWindowUserPointer(mRenderWindow->GetWindow(), this);
	glfwSetWindowSizeCallback(mRenderWindow->GetWindow(), WindowSizeChangedCallback);
	//vsync
	glfwSwapInterval(1);
	//Loading glad?
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	//glfwSetInputMode(mRenderWindow->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwSetCursorPosCallback(mRenderWindow->GetWindow(), mouse_callback);
	glfwSetScrollCallback(mRenderWindow->GetWindow(), scroll_callback);

	glEnable(GL_DEPTH_TEST);
	//Need a registry for every scene, only one scene here
	Registry* registry = new Registry();
	Registry::Instance(); // Just in case
	//Scene Manager 
	mSceneManager = new SceneManager();
	//Scripting manager to handle all lua and native scripting
	mScriptingManager = new ScriptingManager();
	//A shader manager to store all shaders
	mShaderManager = new ShaderManager();
	
	mScene = new Scene(*mShaderManager);
	mScene->Init();
	mSceneManager->AddScene(*mScene);

	// Time between current frame and last frame
	// Time of last frame

	while (!glfwWindowShouldClose(mRenderWindow->GetWindow()))
	{
		//Get events
		glfwPollEvents();

		CalculateDeltaTime();
		
		//Process input
		ProcessInput();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Draw our first triangle
		glUseProgram(mShaderManager->GetShader("PlainShader")->GetProgram());
		//Rendering

		//Update ga
		
		mScene->OnUpdate(deltaTime);


		glfwSwapBuffers(mRenderWindow->GetWindow());
		
	}

	glfwTerminate();

	return 0;
}
    

void MyGE::ProcessInput()
{
    if (glfwGetKey(mRenderWindow->GetWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        std::cout << "Escape Pressed" << std::endl;
        glfwSetWindowShouldClose(mRenderWindow->GetWindow(), true);
    }
    if (glfwGetKey(mRenderWindow->GetWindow(), GLFW_KEY_W) == GLFW_PRESS) {
        std::cout << "Move forward" << std::endl;
      
    }

	if (glfwGetKey(mRenderWindow->GetWindow(), GLFW_KEY_W) == GLFW_PRESS) {
		auto camera = Registry::Instance().GetComponents <CameraComponent>();
		for (int i = 0; i < camera.size(); i++) {
			if (camera[i]->bIsMainCamera) {

				auto& transform = Registry::Instance().GetComponent<TransformComponent>(camera[i]->mGameObjectID);
				transform.mMatrix = glm::translate(transform.mMatrix,camera[i]->mForward);
			}
		}
	}

	if (glfwGetKey(mRenderWindow->GetWindow(), GLFW_KEY_S) == GLFW_PRESS) {
		auto camera = Registry::Instance().GetComponents <CameraComponent>();
		for (int i = 0; i < camera.size(); i++) {
			if (camera[i]->bIsMainCamera) {

				auto& transform = Registry::Instance().GetComponent<TransformComponent>(camera[i]->mGameObjectID);
				transform.mMatrix = glm::translate(transform.mMatrix, -camera[i]->mForward);
			}
		}
	}

	if (glfwGetKey(mRenderWindow->GetWindow(), GLFW_KEY_A) == GLFW_PRESS) {
		auto camera = Registry::Instance().GetComponents <CameraComponent>();
		for (int i = 0; i < camera.size(); i++) {
			if (camera[i]->bIsMainCamera) {

				auto& transform = Registry::Instance().GetComponent<TransformComponent>(camera[i]->mGameObjectID);
				transform.mMatrix = glm::translate(transform.mMatrix, camera[i]->mRight);
			}
		}
	}

	if (glfwGetKey(mRenderWindow->GetWindow(), GLFW_KEY_D) == GLFW_PRESS) {
		auto camera = Registry::Instance().GetComponents <CameraComponent>();
		for (int i = 0; i < camera.size(); i++) {
			if (camera[i]->bIsMainCamera) {

				auto& transform = Registry::Instance().GetComponent<TransformComponent>(camera[i]->mGameObjectID);
				transform.mMatrix = glm::translate(transform.mMatrix, -camera[i]->mRight);
			}
		}
	}
    
}

void mouse_callback(GLFWwindow * window, double xposIn, double yposIn)
{
	return;
	auto cameras = Registry::Instance().GetComponents<CameraComponent>();
	for (size_t i = 0; i < cameras.size(); i++) {
		if (cameras[i]->bIsMainCamera) {
			std::cout << "Doing camera" << std::endl;
			// Hides mouse cursor
			  // Prevents camera from jumping on the first click
			//Gets the current position of the mouse cursor

			double xpos, ypos;
			glfwGetCursorPos(glfwGetCurrentContext(), &xpos, &ypos);

			std::cout << "Camera pos : " << xpos << ", " << ypos << std::endl;

			//Find how for the mouse traveled this frame
			float xoffset = xpos - cameras[i]->mLastPosition.x;
			float yoffset = cameras[i]->mLastPosition.y - ypos;

			std::cout << "Camera offset : " << xoffset << ", " << yoffset << std::endl;
			//Set the current position to the last pos  
			cameras[i]->mLastPosition.x = xpos;
			cameras[i]->mLastPosition.y = ypos;
			std::cout << "Camera last pos : " << cameras[i]->mLastPosition.x << ", " << cameras[i]->mLastPosition.y << std::endl;

			xoffset *= 0.1f;
			yoffset *= 0.1f;
			cameras[i]->mYaw += xoffset;
			cameras[i]->mPitch += yoffset;

			if (cameras[i]->mPitch > 89.0f)
				cameras[i]->mPitch = 89.0f;
			if (cameras[i]->mPitch < -89.0f)
				cameras[i]->mPitch = -89.0f;

			glm::vec3 direction;
			direction.x = cos(glm::radians(cameras[i]->mYaw)) * cos(glm::radians(cameras[i]->mPitch));
			direction.y = sin(glm::radians(cameras[i]->mPitch));
			direction.z = sin(glm::radians(cameras[i]->mYaw)) * cos(glm::radians(cameras[i]->mPitch));
			cameras[i]->mForward = glm::normalize(direction);

			////Calculate mForward, mRight and mUP
			//cameras[i]->mRight = glm::cross(cameras[i]->mForward, cameras[i]->mUp);
			//cameras[i]->mUp = glm::cross(cameras[i]->mForward, cameras[i]->mRight);
			 //Calculate a new rotation
			 // Sets mouse cursor to the middle of the screen so that it doesn't end up roaming around
			glfwSetCursorPos(glfwGetCurrentContext(), 600, 400);
		}
	}
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

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	
}
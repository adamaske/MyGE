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
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

MyGE::MyGE() {
 
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
	mRenderWindow->Init(glfwCreateWindow(1200, 800, "MyGE", NULL, NULL));

	glfwSwapInterval(1);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	//glfwSetInputMode(mRenderWindow->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwSetCursorPosCallback(mRenderWindow->GetWindow(), mouse_callback);
	glfwSetScrollCallback(mRenderWindow->GetWindow(), scroll_callback);

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

	float deltaTime = 0.0f;	// Time between current frame and last frame
	float lastFrame = 0.0f; // Time of last frame

	while (!glfwWindowShouldClose(mRenderWindow->GetWindow()))
	{
		glfwPollEvents();
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		//Process input
		ProcessInput();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Draw our first triangle
		glUseProgram(mShaderManager->GetShader("PlainShader")->GetProgram());
		//Rendering

		//Update game
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
				transform.mMatrix;
			}
		}
	}

	if (glfwGetKey(mRenderWindow->GetWindow(), GLFW_KEY_S) == GLFW_PRESS) {
		auto camera = Registry::Instance().GetComponents <CameraComponent>();
		for (int i = 0; i < camera.size(); i++) {
			if (camera[i]->bIsMainCamera) {

				auto& transform = Registry::Instance().GetComponent<TransformComponent>(camera[i]->mGameObjectID);
				transform.mMatrix[3].z -= 1 / 60.f;
			}
		}
	}

	if (glfwGetKey(mRenderWindow->GetWindow(), GLFW_KEY_A) == GLFW_PRESS) {
		auto camera = Registry::Instance().GetComponents <CameraComponent>();
		for (int i = 0; i < camera.size(); i++) {
			if (camera[i]->bIsMainCamera) {

				auto& transform = Registry::Instance().GetComponent<TransformComponent>(camera[i]->mGameObjectID);
				transform.mMatrix[3].x += 1 / 60.f;
			}
		}
	}

	if (glfwGetKey(mRenderWindow->GetWindow(), GLFW_KEY_D) == GLFW_PRESS) {
		auto camera = Registry::Instance().GetComponents <CameraComponent>();
		for (int i = 0; i < camera.size(); i++) {
			if (camera[i]->bIsMainCamera) {

				auto& transform = Registry::Instance().GetComponent<TransformComponent>(camera[i]->mGameObjectID);
				transform.mMatrix[3].x -= 1 / 60.f;
			}
		}
	}
    
}

void mouse_callback(GLFWwindow * window, double xposIn, double yposIn)
{
	

};

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	
}
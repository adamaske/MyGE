#include "RenderWindow.h"
#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Scene.h"
#include "Components.h"

float vertices[] = {
		 0.5f,  0.5f, 0.0f,  // top right
		 0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f   // top left 
};
unsigned int indices[] = {  // note that we start from 0!
	0, 1, 3,  // first Triangle
	1, 2, 3   // second Triangle
};

RenderWindow::RenderWindow(){
	std::cout << "RenderWindow created!" << std::endl;
}
void RenderWindow::Init(GLFWwindow* window)
{
	std::cout << "RenderWindow initiated!" << std::endl;
	mWindow = window;
	glfwInit();
	//Make context current
	
	glfwMakeContextCurrent(mWindow);
	//glViewport(0, 0, 800, 600);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
	}
	glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
	
}

void RenderWindow::PreRender()
{
	std::cout << "RenderWindow PreRender" << std::endl;
}

void RenderWindow::Render() {
	std::cout << "RenderWindow : Render started!" << std::endl;
	
	glClear(GL_COLOR_BUFFER_BIT);

	
	//Drawing
	//Cant draw without a scene
	if (mActiveScene) {
		//Find all rendercomponents in the scene
		std::vector<RenderComponent*> render = mActiveScene->GetRenders();
		for (int i = 0; i < render.size(); i++)
		{
			render[i]->Render();
		}
		CameraComponent* camera = mActiveScene->GetActiveCamera();
		mActiveScene->GetActiveSceneShader()->SetUniformMatrix4(camera->GetViewMatrix(), "vMatrix");
		mActiveScene->GetActiveSceneShader()->SetUniformMatrix4(camera->GetProjectionMatrix(), "pMatrix");
	
		
	}
	
	// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
	// -------------------------------------------------------------------------------
	glfwSwapBuffers(GetWindow());
	glfwPollEvents();


	glBindVertexArray(0); // no need to unbind it every time 
	std::cout << "RenderWindow : Render finished!" << std::endl;
}

void RenderWindow::SetActiveScene(Scene* scene)
{
	mActiveScene = scene;
}

Scene* RenderWindow::GetActiveScene()
{
	return mActiveScene;
}

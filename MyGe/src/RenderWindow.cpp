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
	//general OpenGL stuff:
	glEnable(GL_DEPTH_TEST);            //enables depth sorting - must then use GL_DEPTH_BUFFER_BIT in glClear
	//    glEnable(GL_CULL_FACE);       //draws only front side of models - usually what you want - test it out!
	glClearColor(0.4f, 0.4f, 0.4f, 1.0f);    //gray color used in glClear GL_COLOR_BUFFER_BIT
	glBindVertexArray(0);
}

void RenderWindow::Render() {
	std::cout << std::endl << std::endl << "----RenderWindow : Render started!" << std::endl << std::endl << std::endl;
	glfwInit();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//Drawing
	//Cant draw without a scene
	if (mActiveScene) {
		//Find all rendercomponents in the scene
		std::vector<RenderComponent*> render = mActiveScene->GetRenders();
		for (int i = 0; i < render.size(); i++)
		{
			
			render[i]->Render();
		}
	
	}
	
	// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
	// -------------------------------------------------------------------------------
	glfwSwapBuffers(mWindow);
	glfwPollEvents();

	std::cout << std::endl << std::endl << "-----RenderWindow : Render finished!" << std::endl << std::endl << std::endl;
	
}

void RenderWindow::SetActiveScene(Scene* scene)
{
	mActiveScene = scene;
}

Scene* RenderWindow::GetActiveScene()
{
	return mActiveScene;
}

#include "pch.h"
#include "RenderWindow.h"

#include "Scenes/Scene.h"
#include "Components/Components.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

RenderWindow::RenderWindow(){
	std::cout << "RenderWindow created!" << std::endl;
}

void RenderWindow::Init(GLFWwindow* window)
{
	mWindow = window;
	//If the window could not open, terminate
	if (mWindow == NULL) {
		std::cout << "MyGE : Failed to create GLFW Window" << std::endl;
		glfwTerminate();
		return;
	}
	//Keeps the screen correct
	glfwSetFramebufferSizeCallback(mWindow, framebuffer_size_callback);

	glfwMakeContextCurrent(mWindow);

}

void RenderWindow::Render(float deltaTime) {
	
}



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
	
}
int RenderWindow::Init(GLFWwindow* window)
{
	mWindow = window;
	if (mWindow == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		//glfwTerminate();
		return 1;
	}

	//Make context current
	glfwMakeContextCurrent(mWindow);
	glViewport(0, 0, 800, 600);
	
	return 0;
}

void RenderWindow::Render() {
	
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	
	glBindVertexArray(0); // no need to unbind it every time 

	//Draw function
	if (mActiveScene) {
		//CubeMeshRenderComponent
		for (int i = 0; i < mActiveScene->mRenderComponents.size(); i++)
		{
			glUseProgram(mActiveScene->mRenderComponents[i]->mShader->GetProgram());

			glBindVertexArray(mActiveScene->mRenderComponents[i]->mVAO);
			glDrawElements(GL_TRIANGLES, mActiveScene->mRenderComponents[i]->mIndices.size(), GL_UNSIGNED_INT, nullptr);
			glBindVertexArray(0);
		}
	}

	// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
	// -------------------------------------------------------------------------------
	glfwSwapBuffers(GetWindow());
	glfwPollEvents();
}

void RenderWindow::SetActiveScene(Scene* scene)
{
	mActiveScene = scene;
}

Scene* RenderWindow::GetActiveScene()
{
	return mActiveScene;
}

#include "RenderWindow.h"
#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Scene.h"
#include "Components.h"

RenderWindow::RenderWindow(){
	std::cout << "RenderWindow created!" << std::endl;
}
void RenderWindow::Init(GLFWwindow* window)
{
	//std::cout << "RenderWindow initiated!" << std::endl;
	//mWindow = window;
	//glfwInit();
	////Make context current
	//
	//glfwMakeContextCurrent(mWindow);
	////glViewport(0, 0, 800, 600);
	//if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	//{
	//	std::cout << "Failed to initialize GLAD" << std::endl;
	//}
	////general OpenGL stuff:
	//glEnable(GL_DEPTH_TEST);            //enables depth sorting - must then use GL_DEPTH_BUFFER_BIT in glClear
	////    glEnable(GL_CULL_FACE);       //draws only front side of models - usually what you want - test it out!
	//glClearColor(0.4f, 0.4f, 0.4f, 1.0f);    //gray color used in glClear GL_COLOR_BUFFER_BIT
	//glBindVertexArray(0);
}

void RenderWindow::Render() {
	//std::cout << std::endl << std::endl << "----RenderWindow : Render started!" << std::endl << std::endl << std::endl;
	//glfwInit();
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//
	////Drawing
	////Cant draw without a scene
	//if (mActiveScene) {
	//	//Find all rendercomponents in the scene
	//	auto render = Registry::Instance().GetObjects<RenderComponent>();
	//	for (auto it = render.begin(); it != render.end(); it++)
	//	{
	//		////Get my shader
	//		//auto shader = Registry::GetObject<ShaderComponent>((*it).mGameObjectID);
	//		//
	//		////Get my transform
	//		//auto transform = Registry::GetObject<TransformComponent>((*it).mGameObjectID);
	//		//
	//		////Get mesh component
	//		//auto mesh = Registry::GetObject<MeshComponent>((*it).mGameObjectID);
	//		//
	//		////Get material component
	//		//auto material = Registry::GetObject<MaterialComponent>((*it).mGameObjectID);
	//		//
	//		////Send my model matrix, get the actual shader from the shaderID of the shader component, and send the transform, operator override
	//		//Registry::GetObject<Shader>(shader.mShaderID).SetUniformMatrix4(transform.mMatrix, "mMatrix");
	//		//
	//		////Draw object
	//		//glBindVertexArray((*it).mVAO);
	//		//glDrawElements(GL_TRIANGLES, mesh.mIndices.size(), GL_UNSIGNED_INT, nullptr);
	//		//glBindVertexArray(0);
	//		//std::cout << "RenderComponent : Render End!" << std::endl;
	//	}
	//
	//}
	//
	//// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
	//// -------------------------------------------------------------------------------
	//glfwSwapBuffers(mWindow);
	//glfwPollEvents();

	std::cout << std::endl << std::endl << "-----RenderWindow : Render finished!" << std::endl << std::endl << std::endl;
	
}



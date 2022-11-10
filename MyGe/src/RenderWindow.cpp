#include "RenderWindow.h"
#include <iostream>
#include "Scene.h"
#include "Components.h"


RenderWindow::RenderWindow() {
	std::cout << "RenderWindow created!" << std::endl;
}
//void RenderWindow::Init(GLFWwindow* window)
//{
//	std::cout << "RenderWindow initiated!" << std::endl;
//	mWindow = window;
//}

//void RenderWindow::Render() {
//	
//	std::cout << std::endl << std::endl << "----RenderWindow : Render started!" << std::endl << std::endl << std::endl;
//	//Drawing
//	//Cant draw without a scene
//	if (mActiveScene) {
//		//Find all rendercomponents in the scene
//		Registry::Instance();
//		return;
//		//auto render = Registry::Instance().GetObjects<RenderComponent>();
//		return;
//		std::vector<RenderComponent> render;
//		//Get my shader
//		auto shader = Registry::Registry::Instance().GetComponents<ShaderComponent>();
//
//		//Get my transform
//		auto transform = Registry::Instance().GetComponents<TransformComponent>();
//
//		//Get mesh component
//		auto mesh = Registry::Instance().GetComponents<MeshComponent>();;
//
//		//Get material component
//		auto material = Registry::Registry::Instance().GetComponents<MaterialComponent>();
//
//		for (auto it = render.begin(); it != render.end(); it++)
//		{
//			
//			
//			
//			//Send my model matrix, get the actual shader from the shaderID of the shader component, and send the transform, operator override
//			//Registry::Instance().GetComponents<Shader>().SetUniformMatrix4(glm::mat4(1), "mMatrix");
//			MeshComponent mesh;
//			//Draw object
//			glBindVertexArray((*it).mVAO);
//			glDrawElements(GL_TRIANGLES, mesh.mIndices.size(), GL_UNSIGNED_INT, nullptr);
//			glBindVertexArray(0);
//			std::cout << "RenderComponent : Render End!" << std::endl;
//		}
//	
//	}
//	std::cout << std::endl << std::endl << "-----RenderWindow : Render finished!" << std::endl << std::endl << std::endl;
//	
//}



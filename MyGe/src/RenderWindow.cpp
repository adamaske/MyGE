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

void RenderWindow::PreRender()
{
	if (mActiveScene) {
		//mActiveScene->Init();
	}
	////Init function
	//if (mActiveScene) {
	//	//CubeMeshRenderComponent
	//	for (int i = 0; i < mActiveScene->mRenderComponents.size(); i++)
	//	{
	//		//initializeOpenGLFunctions();
	//		//Get the model matrix from shader
	//		mActiveScene->mRenderComponents[i]->mMatrixUniform = glGetUniformLocation(mActiveScene->mRenderComponents[i]->mShader->GetProgram(), "mMatrix");
	//		//Vertex array object-VAO
	//		glGenVertexArrays(1, &mActiveScene->mRenderComponents[i]->mVAO);
	//		glBindVertexArray(mActiveScene->mRenderComponents[i]->mVAO);
	//
	//		//Vertex buffer object to hold vertices - VBO
	//		glGenBuffers(1, &mActiveScene->mRenderComponents[i]->mVBO);
	//		glBindBuffer(GL_ARRAY_BUFFER, mActiveScene->mRenderComponents[i]->mVBO);
	//
	//		glBufferData(GL_ARRAY_BUFFER, mActiveScene->mRenderComponents[i]->mVertices.size() * sizeof(Vertex), &mActiveScene->mRenderComponents[i]->mVertices[0], GL_STATIC_DRAW);
	//
	//		//Verts
	//		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
	//		glEnableVertexAttribArray(0);
	//		//Colors
	//		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(3 * sizeof(GLfloat)));
	//		glEnableVertexAttribArray(1);
	//		//uvs
	//		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(6 * sizeof(GLfloat)));
	//		glEnableVertexAttribArray(2);
	//
	//		// Element array buffer - EAB
	//		glGenBuffers(1, &mActiveScene->mRenderComponents[i]->mEAB);
	//		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mActiveScene->mRenderComponents[i]->mEAB);
	//		glBufferData(GL_ELEMENT_ARRAY_BUFFER, mActiveScene->mRenderComponents[i]->mIndices.size() * sizeof(GLuint), mIndices.data(), GL_STATIC_DRAW);
	//
	//
	//		//
	//		//glActiveTexture(GL_TEXTURE1);
	//		//glBindTexture(GL_TEXTURE_2D, mTexture->id());
	//		//if (mActiveScene->mRenderComponents[i]->mTexture) {
	//		//	mActiveScene->mRenderComponents[i]->mTextureUniform = glGetUniformLocation(mShader->getProgram(), "textureSampler");
	//		//}
	//		glBindVertexArray(0);
	//	}
	//}
}

void RenderWindow::Render() {
	
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	
	glBindVertexArray(0); // no need to unbind it every time 

	//Draw function
	//if (mActiveScene) {
	//	//CubeMeshRenderComponent
	//	for (int i = 0; i < mActiveScene->mRenderComponents.size(); i++)
	//	{
	//		glUseProgram(mActiveScene->mRenderComponents[i]->mShader->GetProgram());
	//
	//		//Send my model matrix
	//		mActiveScene->mRenderComponents[i]->mShader->SetUniformMatrix4fv(mActiveScene->mRenderComponents[i]->mMatrix, "mMatrix");
	//
	//		glBindVertexArray(mActiveScene->mRenderComponents[i]->mVAO);
	//		glDrawElements(GL_TRIANGLES, mActiveScene->mRenderComponents[i]->mIndices.size(), GL_UNSIGNED_INT, nullptr);
	//		glBindVertexArray(0);
	//	}
	//}

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

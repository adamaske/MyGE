#include "MyGE.h"
#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "MainWindow.h"
#include "RenderWindow.h"
#include "Scene.h"
#include "ScriptingManager.h"
#include "ShaderManager.h"
#include "Shader.h"

MyGE::MyGE() {
    
}
int MyGE::run()
{
    //Init gl
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //Our window into the game world is a RenderWindow
    mWindow = new RenderWindow();
    //Init, close if not sucess
    mWindow->Init(glfwCreateWindow(800, 600, "MyGE", NULL, NULL));
 
    glfwSwapInterval(1);
    //In this demo I will render 1 secen
    Registry r = Registry();
    Scene* scene = new Scene(r);
    //The render window knows what scene to render
    //mWindow->SetActiveScene(scene);
    
    //Creates registry instance
    Registry::Instance();

    //ScriptingManager scripting = ScriptingManager();
    //mScriptingManager = &scripting;
    //mScriptingManager->Init();
    //
    SceneManager scenemanager = SceneManager();
    mSceneManager = &scenemanager;
    mSceneManager->AddScene(*scene);

    ShaderManager shaderManager = ShaderManager();
    mShaderManager = &shaderManager;

    //Init
    mSceneManager->GetScene()->Init(mShaderManager);
    //The render window knows what scene to render
    //mWindow->SetActiveScene(mSceneManager->GetScene());
    //Main loop
    while (!mWindow->ShouldCloseWindow()) {
        double time = glfwGetTime();
        //Process input
        ProcessInput();
        //Change Game
        mSceneManager->GetScene()->OnUpdate();
        
        //Render
        mWindow->Render();
    }
    
    glfwDestroyWindow(mRenderWindow);
    glfwTerminate();
    return 0;
}

void MyGE::ProcessInput()
{
    if (glfwGetKey(mWindow->GetWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        std::cout << "Escape Pressed" << std::endl;
        glfwSetWindowShouldClose(mWindow->GetWindow(), true);
    }
    if (glfwGetKey(mWindow->GetWindow(), GLFW_KEY_W) == GLFW_PRESS) {
        std::cout << "Move forward" << std::endl;
      
    }
    if (glfwGetKey(mWindow->GetWindow(), GLFW_KEY_N) == GLFW_PRESS) {
        std::cout << "Move forward" << std::endl;
        //Launches new scene
        Scene* s = mSceneManager->GetNextScene(1);
        //Init the scene
        s->Init(mShaderManager);
        //The render window knows what scene to render
        //mWindow->SetActiveScene(s);
    }

    // Handles mouse inputs
	if (glfwGetMouseButton(mRenderWindow, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		// Hides mouse cursor
		glfwSetInputMode(mRenderWindow, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

		// Prevents camera from jumping on the first click
		if (firstClick)
		{
			glfwSetCursorPos(mRenderWindow, (width / 2), (height / 2));
			firstClick = false;
		}

		// Stores the coordinates of the cursor
		double mouseX;
		double mouseY;
		// Fetches the coordinates of the cursor
		glfwGetCursorPos(window, &mouseX, &mouseY);

		// Normalizes and shifts the coordinates of the cursor such that they begin in the middle of the screen
		// and then "transforms" them into degrees 
		float rotX = sensitivity * (float)(mouseY - (height / 2)) / height;
		float rotY = sensitivity * (float)(mouseX - (width / 2)) / width;

		// Calculates upcoming vertical change in the Orientation
		glm::vec3 newOrientation = glm::rotate(Orientation, glm::radians(-rotX), glm::normalize(glm::cross(Orientation, Up)));

		// Decides whether or not the next vertical Orientation is legal or not
		if (abs(glm::angle(newOrientation, Up) - glm::radians(90.0f)) <= glm::radians(85.0f))
		{
			Orientation = newOrientation;
		}

		// Rotates the Orientation left and right
		Orientation = glm::rotate(Orientation, glm::radians(-rotY), Up);

		// Sets mouse cursor to the middle of the screen so that it doesn't end up roaming around
		glfwSetCursorPos(window, (width / 2), (height / 2));
	}
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
	{
		// Unhides cursor since camera is not looking around anymore
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		// Makes sure the next time the camera looks around it doesn't jump
		firstClick = true;
	}
}



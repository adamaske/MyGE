#include "pch.h"
#include "Input.h"

Input::Input() {
	
}

void Input::Init() {
	// Set up GLFW callbacks for key, mouse button, and cursor position events.
	glfwSetKeyCallback(glfwGetCurrentContext(), KeyCallback);
	glfwSetMouseButtonCallback(glfwGetCurrentContext(), MouseButtonCallback);
	glfwSetCursorPosCallback(glfwGetCurrentContext(), CursorPosCallback);
}
bool Input::IsKeyDown(int key)
{
	return GetInstance().mKeys[key] == GLFW_PRESS;
}

bool Input::IsKeyReleased(int key)
{
	return GetInstance().mKeys[key] == GLFW_RELEASE;
}

float Input::MouseX()
{
	return 0.0f;
}

float Input::MouseY()
{
	return 0.0f;
}

void Input::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	//GetInstance().mouseX[key] = action;
	GetInstance().mKeys[key] = action;
}

void Input::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {

}

void Input::CursorPosCallback(GLFWwindow* window, double xpos, double ypos) {
}

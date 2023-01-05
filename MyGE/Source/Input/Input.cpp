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

bool Input::IsMouseButtonDown(int button)
{
	
	return GetInstance().mKeys[button] == GLFW_PRESS;
}

bool Input::IsMouseButtonPressed(int button)
{
	//We can deal with the first click here?
	if (GetInstance().mFirstClicks[button]) {
		//set to false again, we dealt with it
		GetInstance().mFirstClicks[button] = false;
		return true;
	}
	else {
		return false;
	}
}

float Input::MouseX()
{
	return GetInstance().mMouseX;
}

float Input::MouseY()
{
	return GetInstance().mMouseY;
}

float Input::DeltaMouseX()
{
	return GetInstance().mDeltaMouseX;
}

float Input::DeltaMouseY()
{
	return GetInstance().mDeltaMouseY;
}

void Input::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	//GetInstance().mouseX[key] = action;
	GetInstance().mKeys[key] = action;
}

void Input::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
	//Gonna deal with it in the editorcamera
	//GetInstance().mouseX[key] = action;
	//if (action == GLFW_PRESS) {
	//	//This is a press event, check for first mouse
	//	if (GetInstance().bMouseClick) {
	//		//If the mouse is clicked already, set it to false;
	//		GetInstance().bMouseClick = false;
	//	}
	//	//we now know when the pressed
	//}
	//else if (action == GLFW_RELEASE) {
	//	////this is a release event
	//	//if (GetInstance().bMouseClick) {
	//	//	//If the mouse is clicked already, set it to false;
	//	//	GetInstance().bMouseClick = false;
	//	//}
	//}
	GetInstance().mKeys[button] = action;
}

void Input::CursorPosCallback(GLFWwindow* window, double xpos, double ypos) {
	GetInstance().mDeltaMouseX = xpos - GetInstance().mMouseX;
	GetInstance().mDeltaMouseY = ypos - GetInstance().mMouseY;
	GetInstance().mMouseX =	xpos;
	GetInstance().mMouseY =	ypos;
}

#include "pch.h"
#include "Input.h"

Input::Input() {
	
}
bool Input::IsKeyDown(int key) 
{
	return GetInstance().IsKeyDownImplentation(key);
}

bool Input::IsKeyDownImplentation(int key)
{
	auto window = glfwGetCurrentContext();
	return glfwGetKey(window, key) == GLFW_PRESS ? true : false;
}

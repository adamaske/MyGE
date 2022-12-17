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
	auto pressed = glfwGetKey(window, key);
	if (pressed == GLFW_PRESS) {
		return true;
	}
	return false;
}

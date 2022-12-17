#include "pch.h"
#include "Input.h"

bool Input::IsKeyDown(int key) 
{
	auto window = glfwGetCurrentContext();
	auto pressed = glfwGetKey(window, key);
	if (pressed == GLFW_PRESS) {
		return true;
	}
	return false;
}

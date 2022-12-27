#include "pch.h"
#include "EditorCamera.h"

void EditorCamera2::OnUpdate(float deltaTime)
{
	if (Input::IsKeyDown(GLFW_KEY_W)) {
		mPosition.z += 1 * deltaTime;
	} 
	if (Input::IsKeyDown(GLFW_KEY_S)) {
		mPosition.z -= 1 * deltaTime;
	}
	if (Input::IsKeyDown(GLFW_KEY_A)) {
		mPosition.x += 1 * deltaTime;
	}
	if (Input::IsKeyDown(GLFW_KEY_D)) {
		mPosition.x -= 1 * deltaTime;
	}

	//mViewMatrix = glm::lookAt(glm::vec3(0, 2, -2), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	//mProjectionMatrix = glm::perspective(glm::radians(mFOV), mAspectRatio, 0.1f, 1000.f);
}

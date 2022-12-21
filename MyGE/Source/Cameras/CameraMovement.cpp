#include "pch.h"
#include "CameraMovement.h"
#include "../Scripting/ScriptableObject.h"

CameraMovement::CameraMovement(GameObject go) : ScriptableObject(go)
{

}

void CameraMovement::Init()
{
	Logger::Log("CAMERA MOVEMENT INIT");
}

void CameraMovement::OnUpdate(float deltaTime)
{
	//Logger::Log("CAMERA MOVEMENT UPDATE");
	if (Input::IsKeyDown(GLFW_KEY_W)) {
		//Move camera forward
		Logger::Log("CAMERA MOVEMENT MOVE FORWARD");
		
	}
	if (Input::IsKeyDown(GLFW_KEY_S)) {
		//Move camera forward
		Logger::Log("CAMERA MOVEMENT MOVE BACKWARDS");
	}
	if (Input::IsKeyDown(GLFW_KEY_A)) {
		//Move camera forward
		Logger::Log("CAMERA MOVEMENT MOVE LEFT");
	}
	if (Input::IsKeyDown(GLFW_KEY_D)) {
		//Move camera forward
		Logger::Log("CAMERA MOVEMENT MOVE RIGHT");
	}
}

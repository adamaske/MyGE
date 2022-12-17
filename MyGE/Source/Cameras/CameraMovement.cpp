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
	Logger::Log("CAMERA MOVEMENT UPDATE");
	return;
	if (Input::IsKeyDown(GLFW_KEY_W)) {
		//Move camera forward
		Logger::Log("CAMERA MOVEMENT MOVE FORWARD");
	}
}

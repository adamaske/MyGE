#include "pch.h"
#include "CameraMovement.h"
#include "../Scripting/ScriptableObject.h"

CameraMovement::CameraMovement(GameObject go) : ScriptableObject(go)
{

}

void CameraMovement::Init()
{
}

void CameraMovement::OnUpdate(float deltaTime)
{
	if (Input::IsKeyDown(GLFW_KEY_W)) {
		//Move camera forward

	}
}

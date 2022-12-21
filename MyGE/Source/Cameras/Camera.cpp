#include "pch.h"
#include "Camera.h"
#include "../Components/Components.h"
Camera::Camera(GameObject go)
{
	//This should not be used
	mCameraComponent = Registry::Instance().RegisterComponent<CameraComponent>(CameraComponent(), go);
}

Camera::Camera(std::shared_ptr<CameraComponent> camera)
{
	mCameraComponent = camera;
}

void Camera::Init() {

}
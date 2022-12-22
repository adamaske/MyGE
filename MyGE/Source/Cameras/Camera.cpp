#include "pch.h"
#include "Camera.h"
#include "../Components/Components.h"
Camera::Camera()
{
	mCameraComponent = std::make_shared<CameraComponent>();
}
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

void Camera::OnUpdate(float deltaTime)
{
	//Set view and projection matrices 
}

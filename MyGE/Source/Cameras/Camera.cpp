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
	//mCameraComponent = Registry::Instance().RegisterComponent<CameraComponent>(CameraComponent(), go);
}

Camera::Camera(std::shared_ptr<CameraComponent> camera)
{
	mCameraComponent = camera;
}

void Camera::Init() {
	//Update matrices
}

void Camera::OnUpdate(float deltaTime)
{
	//mProjectionMatrix = glm::perspective(glm::radians(mFOV), mAspectRatio, 0.1f, 1000.f);
	//mViewMatrix = glm::lookAt(glm::vec3(0, 2, -2), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
}

void Camera::SetViewAndProjectionMatrix()
{
}

glm::mat4 Camera::GetProjectionMatrix()
{
	return glm::mat4(1);
}

glm::mat4 Camera::GetViewMatrix()
{
	return glm::mat4(1);
}

//void Camera::OnUpdate(float deltaTime)
//{
//	//Set view and projection matrices 
//}

//glm::mat4 Camera::GetProjectionMatrix()
//{
//	return mProjectionMatrix;
//}
//glm::mat4 Camera::GetViewMatrix()
//{
//	return mViewMatrix;
//}
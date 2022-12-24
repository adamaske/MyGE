#pragma once

//all of this should be moved to the camera system instead, when "native scripting" the user should never accsess registry 
using GameObject = uint32_t;
class Camera {
public:
	Camera();
	Camera(GameObject go);
	Camera(std::shared_ptr<struct CameraComponent> camera);

	virtual void Init();
	virtual void OnUpdate(float deltaTime);

	void SetViewAndProjectionMatrix();
	//Gets a perspective matrix
	glm::mat4 GetProjectionMatrix();

	//Gets a view matrix
	glm::mat4 GetViewMatrix();

	//When the viewport changes we want to change the aspect ratio
	void SetViewportSize(uint32_t width, uint32_t height) {
		//mViewportWidth = width;
		//mViewportHeight = height;
		//mAspectRatio = (float)mViewportWidth / (float)mViewportHeight;
	}
	
protected:
	


	std::shared_ptr<CameraComponent> mCameraComponent;
};
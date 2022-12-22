#pragma once
using GameObject = uint32_t;
class Camera {
public:
	Camera();
	Camera(GameObject go);
	Camera(std::shared_ptr<struct CameraComponent> camera);

	virtual void Init();
	virtual void OnUpdate(float deltaTime);
	//Gets a perspective matrix
	glm::mat4 GetProjectionMatrix();
	//{
	//	return glm::perspective(glm::radians(mFOV), mAspectRatio, 0.1f, 1000.f);
	//}

	
	//Gets a view matrix
	glm::mat4 GetViewMatrix();
	//{
	//	return glm::lookAt(glm::vec3(0, 2, -2), glm::vec3(0,0,0), glm::vec3(0,1,0));
	//}
	//When the viewport changes we want to change the aspect ratio
	void SetViewportSize(uint32_t width, uint32_t height) {
		mViewportWidth = width;
		mViewportHeight = height;
		mAspectRatio = (float)mViewportWidth / (float)mViewportHeight;
	}
	
protected:
	glm::mat4 mViewMatrix = glm::mat4(1.f);
	glm::mat4 mProjectionMatrix = glm::mat4(1.f);

	uint32_t mViewportWidth = 1920, mViewportHeight = 1080;
	float mAspectRatio = 1.78f;
	float mFOV = 90.f;


	std::shared_ptr<CameraComponent> mCameraComponent;
};
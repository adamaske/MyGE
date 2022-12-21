#pragma once
using GameObject = uint32_t;
class Camera {
public:
	Camera(GameObject go);
	Camera(std::shared_ptr<struct CameraComponent> camera);

	virtual void Init();
	//Gets a perspective matrix
	glm::mat4 GetProjectionMatrix() {
		return glm::perspective(glm::radians(90.f), mAspectRatio, 0.1f, 1000.f);
	}

	virtual void OnUpdate(float deltaTime);
	//Gets a view matrix
	glm::mat4 GetViewMatrix() {
		return glm::mat4(1.f);
	}
	//When the viewport changes we want to change the aspect ratio
	void SetViewportSize(uint32_t width, uint32_t height) {
		mViewportWidth = width;
		mViewportHeight = height;
		mAspectRatio = (float)mViewportWidth / (float)mViewportHeight;
	}
	
private:
	glm::mat4 mViewMatrix;
	glm::mat4 mProjectionMatrix;

	uint32_t mViewportWidth = 1920, mViewportHeight = 1080;
	float mAspectRatio = 1.78f;

	std::shared_ptr<CameraComponent> mCameraComponent;
};
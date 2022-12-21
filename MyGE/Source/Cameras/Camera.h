#pragma once
#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
class Camera {
public:
	void Init();
	//Gets a perspective matrix
	glm::mat4 GetPerspectiveMatrix() {
		return glm::perspective(glm::radians(90.f), mAspectRatio, 0.1f, 1000.f);
	}
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

};
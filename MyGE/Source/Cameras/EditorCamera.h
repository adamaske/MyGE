#pragma once

#include "Camera.h"
class EditorCamera2 : public Camera {
public:

	virtual void OnUpdate(float deltaTime) override;

private:
	glm::vec3 mPosition = glm::vec3(0, 1, 0);

};
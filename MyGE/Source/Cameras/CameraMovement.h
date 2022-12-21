#pragma once

class CameraMovement : public ScriptableObject{
public:
	CameraMovement(GameObject go);

	virtual void Init() override;
	virtual void OnUpdate(float deltaTime) override;


	float mMovementSpeed = 1;

private:



};
#pragma once

class MyGEMode {
public:
	virtual void Init() = 0;

	virtual void OnUpdate(float deltaTime) = 0;
private:
};
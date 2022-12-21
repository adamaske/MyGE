#pragma once

class MyGEMode {
public:
	MyGEMode();
	virtual void Init() = 0;

	virtual void OnUpdate(float deltaTime) = 0;
private:

protected:
	std::shared_ptr<class MyGEEditor> mEditor;
	std::shared_ptr<class MyGERuntime> mRuntime;
};
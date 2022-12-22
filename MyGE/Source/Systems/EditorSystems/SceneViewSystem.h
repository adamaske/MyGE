#pragma once
#include "../System.h"
class SceneViewSystem : public System {
public:
	SceneViewSystem();
	virtual void Init();
	virtual void OnUpdate(float deltaTime);

private:

	std::shared_ptr<class EditorCamera> mEditorCamera;

	std::shared_ptr<class RenderWindow> mSceneViewport;
	void FramebufferResizedImplementation(int width, int height);
	static void FramebufferResizedCallback(struct GLFWwindow* window, int width, int height);
};
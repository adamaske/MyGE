#pragma once

class MyGE
{
public:

	MyGE();

	int run();

	void ProcessInput();

protected:
	class RenderWindow* mWindow{nullptr};

	//class SceneManager* mSceneManager{ nullptr };
	class Scene* mActiveScene{ nullptr };
};


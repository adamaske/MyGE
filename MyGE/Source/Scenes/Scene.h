#pragma once

using GameObject = uint32_t;
class Scene
{
public:
	Scene();

	virtual void Init();

	virtual void OnUpdate(float deltaTime);

private:

	std::unordered_map<const char*, GameObject> mGameObjects;



	int mViewportWidth = 0;
	int mViewportHeight = 0;

};

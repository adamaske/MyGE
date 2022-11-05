#pragma once
#include <iostream>
#include <vector>
class Scene
{
public:
	std::vector<class CubeMeshRenderComponent> mRenderComponents;
	void Init();
};


#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>
#include "Components.h"
#include "GameObject.h"
#include "ShaderManager.h"
#include "Registry.h"

class Scene
{
public:
	Scene(ShaderManager& shader) : mShaderManager(shader) {
		std::cout << "Scene created!" << std::endl;
	};

	virtual void Init();

	virtual void OnUpdate(float deltaTime);


private:
	//The scene wants to know of all the shaders
	ShaderManager& mShaderManager;
	class ObjMeshSystem* mObjMeshSystem;
	std::unordered_map<const char*, class System*> mSystems;
	//TEMPORARY
	int mCameraID = 0;

};

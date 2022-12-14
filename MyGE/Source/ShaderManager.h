#pragma once
#include <iostream>
#include <unordered_map>
#include "MyGE.h"
static class ShaderManager* mSMInstance;
class ShaderManager {
public:

	ShaderManager() {
		Init();
	};
	~ShaderManager() {
		delete mSMInstance;
	}

	static ShaderManager* Instance() {
		if (mSMInstance == nullptr) {
			mSMInstance = new ShaderManager();
		}
		return mSMInstance;
	}
	void Init() {
		mShaders.insert({"TestShader", std::make_shared<Shader>("../Resources/Shaders/testshader.vert",
								"../Resources/Shaders/testshader.frag", "TestShader")});
		mShaders.insert({ "PlainShader", std::make_shared<Shader>("../Resources/Shaders/plainshader.vert",
								"../Resources/Shaders/plainshader.frag", "PlainShader") });
		mShaders.insert({ "PhongShader", std::make_shared<Shader>("../Resources/Shaders/lightshader.vert",
								"../Resources/Shaders/lightshader.frag", "PhongShader") });
		mShaders.insert({ "TextureShader", std::make_shared<Shader>("../Resources/Shaders/plainshader.vert",
								"../Resources/Shaders/plainshader.frag", "TextureShader") });

		auto mShader = GetShader("PlainShader");
		if (mShader) {
			std::cout << "Got shader from GetShader : " << mShader->mName << std::endl;
		}
		mShader = GetShader("PhongShader");
		if (mShader) {
			std::cout << "Got shader from GetShader : " << mShader->mName << std::endl;
		}
		mShader = GetShader("TextureShader");
		if (mShader) {
			std::cout << "Got shader from GetShader : " << mShader->mName << std::endl;
		}
	};

	std::shared_ptr<Shader> GetShader(std::string name) {
		if (mShaders.find(name.c_str()) != mShaders.end()) {

			return mShaders[name.c_str()];
		}
		return nullptr;
	}

	void InsertShader(std::string shaderName, std::shared_ptr < Shader> shader) {

		//Insert the pointer into the map
		mShaders.insert({ shaderName.c_str(), shader});
	}

	void GetCamera(glm::mat4 v, glm::mat4 p) {
		for (auto it = mShaders.begin(); it != mShaders.end(); it++)
		{
			it->second->SetUniformMatrix4(v, "mVmatrix");
			
			it->second->SetUniformMatrix4(p, "mPmatrix");
		}
	}
	

private:
	std::unordered_map<std::string, std::shared_ptr<Shader>> mShaders;
};
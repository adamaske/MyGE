#pragma once
#include <iostream>
#include <unordered_map>
#include "Shader.h"
class ShaderManager {
public:

	ShaderManager() {
		Init();
	};

	void Init() {
		mShaders.insert({ "PlainShader", new Shader("C:/Users/adama/Documents/GitHub/MyGE/Resources/Shaders/plainshader.vert",
								"C:/Users/adama/Documents/GitHub/MyGE/Resources/Shaders/plainshader.frag", "PlainShader") });
		mShaders.insert({ "PhongShader", new Shader("C:/Users/adama/Documents/GitHub/MyGE/Resources/Shaders/lightshader.vert",
								"C:/Users/adama/Documents/GitHub/MyGE/Resources/Shaders/lightshader.frag", "PhongShader") });
		mShaders.insert({ "TextureShader", new Shader("C:/Users/adama/Documents/GitHub/MyGE/Resources/Shaders/plainshader.vert",
								"C:/Users/adama/Documents/GitHub/MyGE/Resources/Shaders/plainshader.frag", "TextureShader") });

		Shader* mShader = GetShader("PlainShader");
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

	Shader* GetShader(std::string name) {
		if (mShaders.find(name.c_str()) != mShaders.end()) {

			return mShaders[name.c_str()];
		}
		return nullptr;
	}

	void InsertShader(std::string shaderName, Shader* shader) {

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
	std::unordered_map<std::string, Shader*> mShaders;
};
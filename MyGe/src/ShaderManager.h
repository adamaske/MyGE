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
		std::string dir = "C:/Users/adama/OneDrive/Dokumenter/GitHub/MyGe/MyGe/Shaders/";
		Shader shader = Shader(	"C:/Users/adama/OneDrive/Dokumenter/GitHub/MyGe/MyGe/src/Shaders/plainshader.vert", 
								"C:/Users/adama/OneDrive/Dokumenter/GitHub/MyGe/MyGe/src/Shaders/plainshader.frag");
		mShaders["PlainShader"] = &shader;

		shader = Shader("C:/Users/adama/OneDrive/Dokumenter/GitHub/MyGe/MyGe/src/Shaders/lightshader.vert",
			"C:/Users/adama/OneDrive/Dokumenter/GitHub/MyGe/MyGe/src/Shaders/lightshader.frag");
		mShaders["PhongShader"] = &shader;

		shader = Shader("C:/Users/adama/OneDrive/Dokumenter/GitHub/MyGe/MyGe/src/Shaders/textureshader.vert",
			"C:/Users/adama/OneDrive/Dokumenter/GitHub/MyGe/MyGe/src/Shaders/textureshader.frag");
		mShaders["TextureShader"] = &shader;

		
	};

	Shader& GetShader(std::string name) {
		return *mShaders["PlainShader"];
	}

	void InsertShader(std::string shaderName, Shader& shader) {
		mShaders[shaderName] = &shader;
		auto a = mShaders.begin();
	}

	void GetCamera(glm::mat4 v, glm::mat4 p) {
		for (auto it = mShaders.begin(); it != mShaders.end(); it++)
		{
			(*it).second->SetUniformMatrix4(v, "mVmatrix");

			(*it).second->SetUniformMatrix4(p, "mPmatrix");
		}
	}
private:
	std::unordered_map<std::string, class Shader*> mShaders;
};
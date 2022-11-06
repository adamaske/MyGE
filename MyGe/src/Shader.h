#pragma once
#include "glad/glad.h"
#include "glm/glm.hpp"
#include "GLFW/glfw3.h"
#include <string>
class Shader
{
public:
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);

	void Use();

	//GLuint GetProgram();

	void SetUniformMatrix4fv(glm::mat4x4 matrix, std::string name);
	void SetUniform3f(float v1, float v2, float v3, std::string name);
	void SetUniformVec3(glm::vec3 v1, std::string name);
	void SetUniform1f(float v1, std::string name);
	void SetUniform1i(int v1, std::string name);

private:
	//Opengl refrence to this entity
	GLuint mProgram;
};


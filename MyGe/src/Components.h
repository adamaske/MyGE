#pragma once
#include <vector>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/matrix.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Vertex.h"
#include "Shader.h"
#include "Registry.h"

//class TransformComponent : public Component {
struct TransformComponent {
	int mGameObjectID = 0;
	glm::mat4 mMatrix;

	glm::mat4 mPosition;
	glm::mat4 mRotation;
	glm::mat4 mScale;

	// Legger til rette for simulering
	glm::vec3 mVelocity;
	//Kollisjoner
	glm::vec3 mSize;
};

struct MaterialComponent {
	int mGameObjectID = 0;
	glm::vec4 mColour;

};

struct MeshComponent {
	int mGameObjectID = 0;
	std::vector<Vertex> mVertices;
	std::vector<GLuint> mIndices;
	std::string mObjFilePath;
};

struct CameraComponent {
	int mGameObjectID = 0;
	bool bIsMainCamera = 1;

	glm::mat4x4* mPmatrix{ nullptr };         // denne,
	glm::mat4x4* mVmatrix{ nullptr };         // og denne, skal legges inn i kameraklasse
	glm::mat4 mViewMatrix;
	glm::mat4 mProjectionMatrix;

	glm::vec3 mUp;
	glm::vec3 mRight;
	glm::vec3 mForward;

	float mFOV;
	float mAspectRatio;
	float mNearPlane;
	float mFarPlane;

	//Incase the camera dosent have a transform component
	glm::vec3 mPosition{ 0,0,0 };
	glm::vec3 mTarget{ 0, 1, 0 };
};

struct RenderComponent {
	int mGameObjectID = 0;
	GLuint mEAB{ 0 };
	GLuint mVAO{ 0 };
	GLuint mVBO{ 0 };

	GLint mTextureUniform{ 0 };
	GLint mMatrixUniform{ 0 };

	bool bRender = true;
};

struct ScriptComponent {
	int mGameObjectID = 0;
	int mScriptID;
};

struct ShaderComponent
{
	int mGameObjectID = 0;
	int mShaderID = 0;
	GLchar* mVertexPath = 0;
	GLchar* mFragmentPath = 0;

	class Shader* mShader;
};
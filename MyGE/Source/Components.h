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
#include "Camera.h"
#include "GUID.h"
#include ""

struct GUIDComponent {
	int mGameObjectID = 0;
	GUID ID;


};

//class TransformComponent : public Component {
struct TransformComponent {
	int mGameObjectID = 1;
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
	int mGameObjectID = 1;
	glm::vec4 mColour;

};

struct MeshComponent {
	int mGameObjectID = 1;
	std::vector<Vertex> mVertices;
	std::vector<uint32_t> mIndices;
	std::string mObjFilePath;
};

struct CameraComponent {
	//I may want this to just be a container for a pointer to a camera
	Camera mCamera;

	int mGameObjectID = 1;
	bool bIsMainCamera = 1;
	bool bFixedAsceptRatio = false;

	glm::mat4x4* mPmatrix{ nullptr };         // denne,
	glm::mat4x4* mVmatrix{ nullptr };         // og denne, skal legges inn i kameraklasse
	glm::mat4 mViewMatrix;
	glm::mat4 mProjectionMatrix;

	glm::vec3 mUp;
	glm::vec3 mRight;
	glm::vec3 mForward;

	glm::vec3 mGlobalUp = { 0,1,0 };
	glm::vec3 mGlobalRight = { 1,0,0 };
	glm::vec3 mGlobalForward = { 0,0,1 };

	float mFOV;
	float mAspectRatio = 4.f / 3.f;
	float mNearPlane;
	float mFarPlane;

	//Incase the camera dosent have a transform component
	float mYaw = 0;
	float mPitch = 0;

	glm::vec3 mLastPosition = glm::vec3(600, 400, 0);
};

struct RenderComponent {
	int mGameObjectID = 1;
	GLuint mEAB;
	GLuint mVAO;
	GLuint mVBO;

	VBO mVBO;
	GLint mTextureUniform{ 0 };
	GLint mMatrixUniform{ 0 };

	bool bRender = true;

};

struct ScriptComponent {
	int mGameObjectID =1;
	int mScriptID = 0;

	const GLchar* mVertexPath;
	const GLchar* mFragmentPath;
};

struct ShaderComponent
{
	int mGameObjectID = 1;
	int mShaderID = 0;
	GLchar* mVertexPath = 0;
	GLchar* mFragmentPath = 0;

	class Shader* mShader;
};
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
#include "Buffer.h"
#include "VertexArray.h"

using GameObject = uint32_t;
struct GUIDComponent {
	GameObject mGO = 0;
	GUID ID;
};

//class TransformComponent : public Component {
struct TransformComponent {
	GameObject mGO = 0;
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
	GameObject mGO = 0;
	glm::vec4 mColour;

};

struct MeshComponent {
	GameObject mGO = 0;
	std::vector<Vertex> mVertices;
	std::vector<uint32_t> mIndices;
	std::string mObjFilePath;
};

struct CameraComponent {
	//I may want this to just be a container for a pointer to a camera
	Camera mCamera;

	GameObject mGO = 0;
	bool bIsMainCamera = 1;
	bool bFixedAsceptRatio = false;

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
	CameraComponent() {
		std::cout << " Created Camera !! React if there is more than one camera, only one should exist" << std::endl;
	};
};

struct RenderComponent {
	GameObject mGO = 0;
	VertexArray* mVAO;
	bool bRender = true;

	uint32_t mVAO_t;
	uint32_t mVBO_t;
	uint32_t mIBO_t;
};

struct ScriptComponent {
	GameObject mGO = 0;
	int mScriptID = 0;

	const GLchar* mVertexPath;
	const GLchar* mFragmentPath;
};

struct ShaderComponent
{
	GameObject mGO = 0;
	int mShaderID = 0;
	GLchar* mVertexPath = 0;
	GLchar* mFragmentPath = 0;

	class Shader* mShader;
};
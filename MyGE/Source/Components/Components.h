#pragma once
#include <vector>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "../glm/glm.hpp"
#include "../glm/gtc/quaternion.hpp"
#include "../glm/matrix.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include "../glm/gtc/type_ptr.hpp"
#include "../Vertex.h"
#include "../Shader.h"
#include "../Camera.h"
#include "../GUID.h"
#include "../Buffer.h"
#include "../VertexArray.h"
#include "AL/al.h"
#include "AL/alc.h"
#include "../Audio/wavfilereader.h"

using GameObject = uint32_t;
struct GUIDComponent {
	GameObject mGO = 0;
	GUID ID;
};

struct AudioSourceComponent {
	GameObject mGO = 0;
	std::string mName;          ///< The name of the sound source (Not used).
	ALuint mSource;             ///< The sound source.
	ALuint mBuffer;             ///< The data buffer.

	const char* mFilePath;
	wave_t mFile;

	float mGain = 1;
	bool bLoop = 0;

	bool bShouldPlay = true;
	bool bPlaying = false;
	bool bShouldStop = false;
};

struct AudioListenerComponent {
	GameObject mGO = 0;

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

	glm::vec3 mForward = { 0,0,1 };
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
	GameObject mGO;

	std::shared_ptr<VertexArray> mVAO;
	std::shared_ptr<VertexBuffer> mVBO;
	std::shared_ptr<IndexBuffer> mIBO;
	bool bRender = true;

	RenderComponent() {
		std::cout << "RENDER COMPONENT CREATED; THERE SHOULD BE ONE CUBE + MONKEY ONLY;" << std::endl;
	}
};

struct ScriptComponent {
	GameObject mGO = 0;
	int mScriptID = 0;

	const GLchar* mVertexPath;
	const GLchar* mFragmentPath;
};

struct NativeScriptComponent {

};
struct ShaderComponent
{
	GameObject mGO = 0;
	int mShaderID = 0;
	GLchar* mVertexPath = 0;
	GLchar* mFragmentPath = 0;

	class Shader* mShader;
};

struct TerrainComponent {
	GameObject mGO = 0;

	enum class TerrainType{ PerlinNoise, LAZFile};
	TerrainType mType  = TerrainType::PerlinNoise;

	std::vector<float> mVertices;
	std::vector<float> mIndicies;

	float mWidth = 200;  
	float mHeight = 200;

	float mResolution = 1;

	const char* mFilePath = "../Resources/Terrain/fullData.txt";
};
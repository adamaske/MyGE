#pragma once
//This should all be in a precompiled header ? 
#include "../Vertex.h"
#include "../Shader.h"
#include "../Cameras/Camera.h"
#include "../GUID.h"
#include "../Rendering/Buffer.h"
#include "../Rendering/VertexArray.h"
#include "../Audio/wavfilereader.h"
#include "../Scripting/ScriptableObject.h"


#include <vector>
#include "AL/al.h"
#include "AL/alc.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "../glm/glm.hpp"
#include "../glm/gtc/quaternion.hpp"
#include "../glm/matrix.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include "../glm/gtc/type_ptr.hpp"

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
	glm::mat4 mMatrix = glm::mat4(1.0f);

	glm::mat4 mPosition = glm::mat4(1.0f);;
	glm::mat4 mRotation = glm::mat4(1.0f);;
	glm::mat4 mScale = glm::mat4(1.0f);;

	// Legger til rette for simulering
	glm::vec3 mVelocity;
	//Kollisjoner
	glm::vec3 mSize;

	glm::vec3 mForward = { 0,0,1 };
};

struct MaterialComponent {
	GameObject mGO = 0;
	glm::vec4 mColour;

	//textures
	std::string mTexturePath = "../Resources/Textures/hammer.bmp";
	std::shared_ptr<class Texture> mTexture;

	//Shaders
	int mShaderID = 0;
	GLchar* mVertexPath = 0;
	GLchar* mFragmentPath = 0;
	std::shared_ptr<class Shader> mShader;

	bool bUseTexture = true;
};

struct MeshComponent {
	GameObject mGO = 0;
	std::string mObjFilePath;
	std::string mMeshName = " Cube ";
};

struct CameraComponent {
	//I may want this to just be a container for a pointer to a camera
	std::shared_ptr<Camera> mCamera;

	GameObject mGO = 0;

	bool bIsMainCamera = 1;
	bool bFixedAsceptRatio = false;

	glm::mat4 mViewMatrix = glm::mat4(1);
	glm::mat4 mProjectionMatrix = glm::mat4(1);

	glm::vec3 mUp = { 0,1,0 };
	glm::vec3 mRight = { 1,0,0 };
	glm::vec3 mForward = { 0,0,1 };

	glm::vec3 mGlobalUp = { 0,1,0 };
	glm::vec3 mGlobalRight = { 1,0,0 };
	glm::vec3 mGlobalForward = { 0,0,1 };

	float mFOV = 90;
	float mAspectRatio = 4.f / 3.f;
	float mNearPlane = 0.1f;
	float mFarPlane = 1000.f;

	//Incase the camera dosent have a transform component
	float mYaw = 0;
	float mPitch = 0;

	glm::vec3 mLastPosition = glm::vec3(600, 400, 0);
};

struct RenderComponent {
	GameObject mGO;

	std::shared_ptr<VertexArray> mVAO;
	std::shared_ptr<VertexBuffer> mVBO;
	std::shared_ptr<IndexBuffer> mIBO;

	GLuint m_VAO;
	GLuint m_VBO;
	GLuint m_IBO;

	bool bRender = true;
	bool bRenderMesh = true;
};

struct ScriptComponent {
	GameObject mGO = 0;
	int mScriptID = 0;

	const GLchar* mVertexPath;
	const GLchar* mFragmentPath;
};

struct NativeScriptComponent {
	GameObject mGO = 0;
	//Pointer
	//This should 
	class ScriptableObject* mObject;
	
	template<typename T>
	void Bind() {
		//We want to bind a specific ScriptableObject to mObject
		//this now sets mObject to a new isntance of T
		mObject = static_cast<ScriptableObject*>(new T(mGO));

	}


	//We want to be able to instantiate this object in run time

	//We should be able to pass any ScriptableObject to this, on rumtine it should then be instantiated and updated i believe
	
	//I want to be able to pass this something like a class "CameraController"
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

	std::shared_ptr<VertexArray> mVAO;
	std::shared_ptr<VertexBuffer> mVBO;
	std::shared_ptr<IndexBuffer> mIBO;
};

struct BillboardComponent {
	GameObject mGO = 0;



};
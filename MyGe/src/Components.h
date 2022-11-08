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
struct TransformComponent{
public:
	int mGameObjectID = 0;

	glm::mat4 mMatrix;

	glm::mat4 mPosition;
	glm::mat4 mRotation;
	glm::mat4 mScale;

	// Legger til rette for simulering
	glm::vec3 mVelocity;
	//Kollisjoner
	glm::vec3 mSize;

	//TransformComponent(int objectID) : Component(objectID) {};

	//virtual void Init() override {
	//	mMatrix = glm::mat4(1.f);
	//	mPosition	= glm::mat4(1.f);
	//	mRotation	= glm::mat4(1.f);
	//	
	//	mScale= glm::mat4(1.f);
	//	// Legger til rette for simulering
	//	mVelocity = glm::vec3(1);
	//	//Kollisjoner
	//	mSize = glm::vec3(1);
	//	std::cout << "TransformComponent : Init" << std::endl;
	//};
	//virtual void OnUpdate(float ts) override {
	//	UpdateTransform();
	//	std::cout << "TransformComponent : OnUpdate" << std::endl;
	//};

	//void UpdateTransform() {
	//	mMatrix = mPosition * mRotation * mScale;
	//	glm::mat4 base(1.f);
	//	base = glm::translate(base, glm::vec3(1, 4, 2));
	//	base = glm::lookAt(glm::vec3(1, 1, -5), glm::vec3(0, 0, 0), glm::vec3(0, 0, 1));
	//	std::cout << base[0].x << base[0].y << base[0].z << base[0].w << std::endl;
	//	std::cout << base[1].x << base[1].y << base[1].z << base[1].w << std::endl;
	//	std::cout << base[2].x << base[2].y << base[2].z << base[2].w << std::endl;
	//	std::cout << base[3].x << base[3].y << base[3].z << base[3].w << std::endl;
	//};

	//operator glm::mat4() { return mMatrix; };
	//glm::mat4 GetTransform() { return mMatrix; };
	//glm::mat4 GetPosition() const {
	//	return mPosition;
	//};
	//glm::vec3 GetPosition() {
	//	return glm::vec3(mPosition[3].x, mPosition[3].y, mPosition[3].z);
	//};
	//void SetPosition(const glm::vec3& position) {
	//	mPosition = glm::mat4(1.f);
	//	mPosition = glm::translate(mPosition, position);
	//};
	//void SetPosition(const glm::mat4& position) {
	//	mPosition = position;
	//};
	//void AddLocalOffset(glm::vec3 offset) {
	//	glm::vec3 off = GetPosition() + offset;
	//	mPosition = glm::mat4(1.f);
	//	mPosition = glm::translate(mPosition, off);
	//}
	//glm::vec3 GetScale() const {
	//	return glm::vec3(mScale[0][0], mScale[1][1], mScale[2][2]);
	//};
	//void SetScale(const glm::vec3& scale);
	//void SetScale(const glm::mat4x4& scale);

	//glm::mat4x4 GetRotation() const;
	//void SetRotation(const glm::vec3& rotation) {
	//	
	//};
	//void rotate(float dx, float dy, float dz);
};

struct MaterialComponent {
public:
	int mGameObjectID = 0;

	glm::vec4 mColour;

};

struct MeshComponent {
public:
	int mGameObjectID = 0;

	std::vector<Vertex> mVertices;
	std::vector<GLuint> mIndices;
	std::string mObjFilePath;
	//MeshComponent(int objectID) : Component(objectID) {};
	//MeshComponent(int objectID, std::string filename) : Component(objectID) {
	//	Init(filename);
	//};
	//~MeshComponent(){};
	//void Init(std::string filename) {
	//
	//	Readfile(filename);
	//};
	//void Init(std::vector<Vertex> verts, std::vector<GLuint> ind) {
	//	mVertices = verts;
	//	mIndices = ind;
	//}
	//void Init(std::vector<Vertex> verts) {
	//	mVertices = verts;
	//
	//}
	//void Readfile(std::string filePath);
	//void WriteFile(std::string filePath);
};

struct CameraComponent{
public:
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
	//CameraComponent(int objectID) :
	//	Component(objectID), mFOV(200), mAspectRatio(18/9), mNearPlane(0.01f), mFarPlane(1000.f) {};
	//CameraComponent(int objectID, int transformID) :
	//	Component(objectID), mTransformID(transformID), mFOV(200), mAspectRatio(18 / 9), mNearPlane(0.01f), mFarPlane(1000.f) {};
	//CameraComponent(int objectID, float fov, float aspect, float near, float far) :
	//	Component(objectID), mFOV(fov), mAspectRatio(aspect), mNearPlane(near), mFarPlane(far) {};
	//void Init() {
	//	mUp		= glm::vec3(0,0,1);
	//	mRight	= glm::vec3(1,0,0);
	//	mForward	= glm::vec3(0,1,0);
	//
	//	mViewMatrix = glm::mat4(1.f);
	//	mProjectionMatrix = glm::mat4(1.f);
	//	
	//};
	//
	//virtual void OnUpdate(float ts) override {
	//	UpdateProjection();
	//	UpdateView();
	//};
	//
	//void UpdateProjection() {
	//	
	//	mProjectionMatrix = glm::perspective(glm::radians(mFOV), mAspectRatio, mNearPlane, mFarPlane);
	//}
	//void UpdateView() {
	//	mViewMatrix = glm::lookAt(mPosition, mPosition + mForward, glm::vec3(0, 1, 0));
	//}
	//
	////Delete later
	//void LookAt(glm::vec3 pos, glm::vec3 at, glm::vec3 up) {
	//	mViewMatrix = glm::lookAt(pos, at, glm::vec3(0, 0, 1));
	//};
	//
	//glm::mat4 GetViewMatrix() { 
	//	glm::mat4 m = Registry::Instance().GetObject<TransformComponent>(mGameObjectID).GetPosition();
	//	glm::vec3 pos = glm::vec3(m[3].x, m[3].y, m[3].z);
	//	return glm::lookAt(pos, pos + glm::vec3(0, 0, 1), mUp); };
	//glm::mat4 GetProjectionMatrix() { return mProjectionMatrix; };
	//

};

struct RenderComponent{
public:
	int mGameObjectID = 0;

	GLuint mEAB{ 0 };
	GLuint mVAO{ 0 };
	GLuint mVBO{ 0 };

	GLint mTextureUniform{ 0 };
	GLint mMatrixUniform{ 0 };
};

struct ScriptComponent{
public:
	int mGameObjectID = 0;
	int mScriptID;
};

struct ShaderComponent
{
	int mGameObjectID = 0;
	int mShaderID = 0;
	GLchar* mVertexPath = 0; 
	GLchar* mFragmentPath = 0;
};

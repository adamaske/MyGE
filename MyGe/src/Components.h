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
class Component {
public:
	Component(class GameObject* parent);
	~Component();

	virtual void Init();
	virtual void Init(class MaterialComponent* material, class TransformComponent* transfrom) {

	};
	virtual void Init(class TransformComponent* transform) {

	};

	virtual void OnUpdate(float ts);

protected:
	GameObject* mParent;
};

class TransformComponent : public Component {
public:
	TransformComponent(GameObject* parent) : Component(parent) {};

	virtual void Init() override {
		mMatrix = glm::mat4(1.f);
		mPosition	= glm::mat4(1.f);
		mRotation	= glm::mat4(1.f);
		
		mScale= glm::mat4(1.f);
		// Legger til rette for simulering
		mVelocity = glm::vec3(1);
		//Kollisjoner
		mSize = glm::vec3(1);
		std::cout << "TransformComponent : Init" << std::endl;
	};
	virtual void OnUpdate(float ts) override {
		UpdateTransform();
		std::cout << "TransformComponent : OnUpdate" << std::endl;
	};

	void UpdateTransform() {
		mMatrix = mPosition * mRotation * mScale;
		glm::mat4 base(1.f);
		base = glm::translate(base, glm::vec3(1, 4, 2));
		base = glm::lookAt(glm::vec3(1, 1, -5), glm::vec3(0, 0, 0), glm::vec3(0, 0, 1));
		std::cout << base[0].x << base[0].y << base[0].z << base[0].w << std::endl;
		std::cout << base[1].x << base[1].y << base[1].z << base[1].w << std::endl;
		std::cout << base[2].x << base[2].y << base[2].z << base[2].w << std::endl;
		std::cout << base[3].x << base[3].y << base[3].z << base[3].w << std::endl;
	};

	glm::mat4 GetTransform() { return mMatrix; };
	glm::mat4 GetPosition() const {
		return mPosition;
	};
	glm::vec3 GetPosition() {
		return glm::vec3(mPosition[3].x, mPosition[3].y, mPosition[3].z);
	};
	void SetPosition(const glm::vec3& position) {
		mPosition = glm::mat4(1.f);
		mPosition = glm::translate(mPosition, position);
	};
	void SetPosition(const glm::mat4& position) {
		mPosition = position;
	};
	void AddLocalOffset(glm::vec3 offset) {
		glm::vec3 off = GetPosition() + offset;
		mPosition = glm::mat4(1.f);
		mPosition = glm::translate(mPosition, off);
	}
	glm::vec3 GetScale() const {
		return glm::vec3(mScale[0][0], mScale[1][1], mScale[2][2]);
	};
	void SetScale(const glm::vec3& scale);
	void SetScale(const glm::mat4x4& scale);

	glm::mat4x4 GetRotation() const;
	void SetRotation(const glm::vec3& rotation) {
		
	};
	void rotate(float dx, float dy, float dz);

private:
	glm::mat4 mMatrix;

	glm::mat4 mPosition;
	glm::mat4 mRotation;
	glm::mat4 mScale;

	// Legger til rette for simulering
	glm::vec3 mVelocity;
	//Kollisjoner
	glm::vec3 mSize;
};

class MaterialComponent : public Component {
public:
	
	MaterialComponent(GameObject* parent): Component(parent) {};
	MaterialComponent(GameObject* parent, Shader* shader) : Component(parent) , mShader(shader) {};
	MaterialComponent(GameObject* parent, Shader* shader, glm::vec4 colour) : Component(parent), mShader(shader), mColour(colour) {};

	Shader* GetShader() { return mShader; };
	void SetShader(Shader* shader) {
		mShader = shader;
	}
private:
	Shader* mShader;
	glm::vec4 mColour;

};

class MeshComponent : public Component {
public:
	MeshComponent(GameObject* parent) : Component(parent) {};
	MeshComponent(GameObject* parent, std::string filename) : Component(parent) { 
		Init(filename);
	};
	~MeshComponent(){};
	void Init(std::string filename) {

		Readfile(filename);
	};
	void Init(std::vector<Vertex> verts, std::vector<GLuint> ind) {
		mVertices = verts;
		mIndices = ind;
	}
	void Init(std::vector<Vertex> verts) {
		mVertices = verts;
	
	}
	void Readfile(std::string filePath);
	void WriteFile(std::string filePath);
protected:
	std::vector<Vertex> mVertices;
	std::vector<GLuint> mIndices;
	friend class RenderComponent;
	
public:
	
};

class CameraComponent : public Component {
public:
	CameraComponent(GameObject* parent) :
		Component(parent), mFOV(200), mAspectRatio(18/9), mNearPlane(0.01f), mFarPlane(1000.f) {};
	CameraComponent(GameObject* parent, float fov, float aspect, float near, float far) : 
		Component(parent), mFOV(fov), mAspectRatio(aspect), mNearPlane(near), mFarPlane(far) {};
	void Init(TransformComponent* transform) {
		mTransform = transform;
		mUp		= glm::vec3(0,0,1);
		mRight	= glm::vec3(1,0,0);
		mForward	= glm::vec3(0,1,0);

		mViewMatrix = glm::mat4(1.f);
		mProjectionMatrix = glm::mat4(1.f);
		
	};

	virtual void OnUpdate(float ts) override {
		UpdateProjection();
		UpdateView();
	};

	void UpdateProjection() {
		
		mProjectionMatrix = glm::perspective(glm::radians(mFOV), mAspectRatio, mNearPlane, mFarPlane);
	}
	void UpdateView() {
		if (mTransform) {
			mViewMatrix = glm::lookAt(glm::vec3(0, 0, -5), glm::vec3(0, 0, 0), mUp);
		}
		else {
			std::cout << "CameraComponent : No transform" << std::endl;
			mViewMatrix = glm::lookAt(mPosition, mPosition + mForward, glm::vec3(0, 1, 0));
		}
		
	}

	//Delete later
	void LookAt(glm::vec3 pos, glm::vec3 at, glm::vec3 up) {
		mViewMatrix = glm::lookAt(pos, at, glm::vec3(0, 0, 1));
	};

	glm::mat4 GetViewMatrix() { return glm::lookAt(mTransform->GetPosition(), mTransform->GetPosition() + glm::vec3(0, 0, 1), mUp); };
	glm::mat4 GetProjectionMatrix() { return mProjectionMatrix; };
private:
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
	glm::vec3 mPosition{0,0,0};
	glm::vec3 mTarget{ 0, 1, 0};
	TransformComponent* mTransform;
};

class RenderComponent : public Component {
public:
	RenderComponent(GameObject* parent) : Component(parent) {};
	
	void Init(MeshComponent* mesh, TransformComponent* transform, MaterialComponent* material) {
		mMesh = mesh;
		mTransform		= transform;
		mMaterial = material;

		//Vertex array object-VAO
		glGenVertexArrays(1, &mVAO);
		glBindVertexArray(mVAO);

		//Vertex buffer object to hold vertices - VBO
		glGenBuffers(1, &mVBO);
		glBindBuffer(GL_ARRAY_BUFFER, mVBO);

		glBufferData(GL_ARRAY_BUFFER, mMesh->mVertices.size() * sizeof(Vertex), &mMesh->mVertices[0], GL_STATIC_DRAW);
		//Verts
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
		glEnableVertexAttribArray(0);
		//Colors
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);
		//uvs
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(6 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);

		// Element array buffer - EAB
		glGenBuffers(1, &mEAB);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEAB);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, mMesh->mIndices.size() * sizeof(GLuint), mMesh->mIndices.data(), GL_STATIC_DRAW);
		glBindVertexArray(0);
		std::cout << "Render init finished!" << std::endl;
	};

	void Render() {
		std::cout << "RenderComponent : Render!" << std::endl;
		//use my shader
		glUseProgram(mMaterial->GetShader()->GetProgram());
		//Send my model matrix
		
		mMaterial->GetShader()->SetUniformMatrix4(mTransform->GetTransform(), "mMatrix");
		//Draw object
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glBindVertexArray(mVAO);
		glDrawElements(GL_TRIANGLES, mMesh->mIndices.size(), GL_UNSIGNED_INT, nullptr);
		glBindVertexArray(0);
		std::cout << "RenderComponent : Render End!" << std::endl;
	};

private:
	MeshComponent* mMesh; 
	TransformComponent* mTransform;
	MaterialComponent* mMaterial;

	GLuint mEAB{ 0 };
	GLuint mVAO{ 0 };
	GLuint mVBO{ 0 };

	GLint mTextureUniform{ 0 };
	GLint mMatrixUniform{ 0 };
};

class ScriptComponent : public Component {
public:
	ScriptComponent(GameObject* parent, int id) : Component(parent), mScriptID(id) {};

	virtual void Init() override;

	virtual void OnUpdate(float ts) override;

	int GetScriptID() { return mScriptID; };
private:
	int mScriptID;
};

#pragma once
#include <vector>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/matrix.hpp"
//#include "glm/mat4x4.hpp"

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

	};
	virtual void OnUpdate(float ts) override {

	};

	void UpdateTransform() {
		mMatrix = mPosition * mRotation * mScale;
	};

	glm::mat4x4 GetTransform() { return mMatrix; };
	glm::mat4x4 GetPosition() const {
		return mPosition;
	};
	glm::vec3 GetPosition() {
		return glm::vec3(mPosition[2][0], mPosition[2][1], mPosition[2][2]);
	};
	void SetPosition(const glm::vec3& position) {
		
	};
	void SetPosition(const glm::mat4x4& position) {
		mPosition = position;
	};

	glm::vec3 GetScale() const {
		return glm::vec3(mScale[0][0], mScale[1][1], mScale[2][2]);
	};
	void SetScale(const glm::vec3& scale);
	void SetScale(const glm::mat4x4& scale);

	glm::mat4x4 GetRotation() const;
	void SetRotation(const glm::vec3& rotation);
	void rotate(float dx, float dy, float dz);

private:
	glm::mat4x4 mMatrix;

	glm::mat4x4 mPosition;
	glm::mat4x4 mRotation;
	glm::mat4x4 mScale;

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
		Component(parent), mFOV(90), mAspectRatio(16/9), mNearPlane(0.01f), mFarPlane(1000.f) {};
	CameraComponent(GameObject* parent, float fov, float aspect, float near, float far) : 
		Component(parent), mFOV(fov), mAspectRatio(aspect), mNearPlane(near), mFarPlane(far) {};
	void init() {
		mUp		= glm::vec3(0,0,1);
		mRight	= glm::vec3(1,0,0);
		mForward	= glm::vec3(0,1,0);

		mViewMatrix = glm::mat4(1.f);
		mViewMatrix = glm::mat4(1.f);
	};

	virtual void OnUpdate(float ts) override {
		UpdateProjection();
		UpdateView();
	};
	void UpdateProjection() {
		mProjectionMatrix = glm::perspective(mFOV, mAspectRatio, mNearPlane, mFarPlane);
	}
	void UpdateView() {
		if (mTransform) {
			//Get transform from transform component
			mViewMatrix = glm::lookAt(mTransform->GetPosition(), mPosition + mForward, mUp);
		}
		else {
			mViewMatrix = glm::lookAt(mPosition, mPosition + mForward, glm::vec3(0, 0, 1));
		}
		
	}

	//Delete later
	void LookAt(glm::vec3 pos, glm::vec3 at, glm::vec3 up) {
		mViewMatrix = glm::lookAt(pos, at, glm::vec3(0, 0, 1));
	};

	glm::mat4 GetViewMatrix() { return mViewMatrix; };
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
		std::cout << "Render init started!" << std::endl;
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
		//use my shader
		glUseProgram(mMaterial->GetShader()->GetProgram());
		//Send my model matrix
		mMaterial->GetShader()->SetUniformMatrix4(mTransform->GetTransform(), "mMatrix");
		//Draw object
		glBindVertexArray(mVAO);
		glDrawElements(GL_TRIANGLES, mMesh->mIndices.size(), GL_UNSIGNED_INT, nullptr);
		glBindVertexArray(0);

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

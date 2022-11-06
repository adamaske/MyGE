#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/mat4x4.hpp"
#include <vector>
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

private:
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
private:
	Shader* mShader;
	glm::vec4 mColour;

};
class MeshComponent : public Component {
public:
	MeshComponent(GameObject* parent) : Component(parent) {};
	~MeshComponent(){};

protected:
	std::vector<Vertex> mVertices;
	std::vector<GLuint> mIndices;
	GLuint mEAB{ 0 };
	GLuint mVAO{ 0 };
	GLuint mVBO{ 0 };
	GLint mTextureUniform{ 0 };
	GLint mMatrixUniform{ 0 };
public:
	MaterialComponent* mMaterial;
	TransformComponent* mTransform;

	virtual void Init(MaterialComponent* material, TransformComponent* transform) override {
		mMaterial = material; 
		mTransform = transform;
		//Get the model matrix from shader
		//mMatrixUniform = glGetUniformLocation(mShader->getProgram(), "mMatrix");
		//Vertex array object-VAO
		glGenVertexArrays(1, &mVAO);
		glBindVertexArray(mVAO);

		//Vertex buffer object to hold vertices - VBO
		glGenBuffers(1, &mVBO);
		glBindBuffer(GL_ARRAY_BUFFER, mVBO);

		glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(Vertex), &mVertices[0], GL_STATIC_DRAW);

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
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndices.size() * sizeof(GLuint), mIndices.data(), GL_STATIC_DRAW);


		//
		//glActiveTexture(GL_TEXTURE1);
		//glBindTexture(GL_TEXTURE_2D, mTexture->id());
		//if (mTexture) {
		//	mTextureUniform = glGetUniformLocation(mShader->getProgram(), "textureSampler");
		//}
		glBindVertexArray(0);
	};
	virtual void OnUpdate(float ts) override {
		//Draw function
		//if (mTexture) {
		//	glActiveTexture(GL_TEXTURE0);
		//	glBindTexture(GL_TEXTURE_2D, mTexture->id());
		//	glUniform1i(mTextureUniform, 0);
		//}
		//use my shader
		//glUseProgram(mMaterial->GetShader()->GetProgram());
		//Send my model matrix
		mMaterial->GetShader()->SetUniformMatrix4fv(mTransform->GetTransform(), "mMatrix");
		//Draw object
		//glBindVertexArray(mVAO);
		//glDrawElements(GL_TRIANGLES, mIndices.size(), GL_UNSIGNED_INT, nullptr);
		//glBindVertexArray(0);
	};

	//std::pair<float, float> GetPosition2D();


};

class CameraComponent : public Component {
public:
	CameraComponent(GameObject* parent) : Component(parent) {};
	virtual void Init(TransformComponent* transform) override;
private:

};

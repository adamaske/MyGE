#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "Vertex.h"
#include "Shader.h"
class Component {
	int mEntity;
};

class TransformComponent {

};

class MaterialComponent {
public:
	Shader* mShader;
	glm::vec4 mColor{1,1,1,1};
};
class CubeMeshRenderComponent {
public:

	Shader* mShader;

	std::vector<Vertex> mVertices;
	std::vector<GLuint> mIndices;

	GLuint mEAB{ 0 };
	GLuint mVAO{ 0 };
	GLuint mVBO{ 0 };

	GLint mTextureUniform{ 0 };
	GLint mMatrixUniform{ 0 };

	glm::mat4 mMatrix;

	glm::mat4 mPosition;
	glm::mat4 mRotation;
	glm::mat4 mScale;
	// Legger til rette for simulering
	glm::vec3 mVelocity;
	//Kollisjoner
	glm::vec3 mSize;

	void init() {
		glEnable(GL_DEPTH_TEST);
		glClearColor(0.4f, 0.4f, 0.4f, 1.0f);


		mMatrixUniform = glGetUniformLocation(mShader->GetProgram(), "mMatrix");
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


	}
};
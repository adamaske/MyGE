#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Buffer.h"
#include "Renderer.h"
#include <vector>
class VertexArray {

public:
	VertexArray() {
		glGenVertexArrays(1, &mVAO);
		glBindVertexArray(mVAO);
	};

	void Bind() {
		glBindVertexArray(mVAO);
	};
	void Unbind() {
		glBindVertexArray(0);
	};

	void Print() {
		for (auto vbo : mVertexBuffers) {
			for (int i = 0; i < 50; i += 8) {
				std::cout << "v1(" << vbo->mVerts[i] << "), " << "v2(" << vbo->mVerts[i + 1] << "), " << "v2(" << vbo->mVerts[i + 2] << ")" << std::endl;

				std::cout << "n1(" << vbo->mVerts[i + 3] << "), " << "n2(" << vbo->mVerts[i + 4] << "), " << "n2(" << vbo->mVerts[i + 5] << ")" << std::endl;
				std::cout << "t1(" << vbo->mVerts[i + 6] << "), " << "t2(" << vbo->mVerts[i + 7] << ")" << std::endl;
			}
			
		}
		std::cout << std::endl;
		for (int i = 0; i < 100; i++) {
			std::cout << mIndexBuffer->mIndices[i];
		}
		std::cout << std::endl;
	}

	void AddVertexBuffer(std::shared_ptr<VertexBuffer> buffer) {
		mVertexBuffers.push_back(buffer);
		//For this vertex buffer, we want to specify the layot
		//So we bind it
		buffer->Bind();
		//Verts
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		//Normals
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		//uvs																
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);

		//Unbinds ? 
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	};
	void AddIndexBuffer(std::shared_ptr<IndexBuffer> buffer) {
		//Use this vertex array
		glBindVertexArray(mVAO);

		//So we bind it
		buffer->Bind();

		mIndexBuffer = buffer;
	};

	std::shared_ptr<IndexBuffer> GetIndexBuffer() {
		return mIndexBuffer;
	}

private:
	uint32_t mVAO = 0;
	std::vector<std::shared_ptr<VertexBuffer>> mVertexBuffers;
	std::shared_ptr<IndexBuffer> mIndexBuffer;
};
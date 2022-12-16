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
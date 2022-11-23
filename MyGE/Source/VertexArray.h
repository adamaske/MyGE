#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Buffer.h"
#include "Renderer.h"
#include <vector>
class VertexArray {

public:
	VertexArray() {
		mRendererID = Renderer::ID();
		glCreateVertexArrays(1, &mRendererID);
	};

	void Bind() {
		glBindVertexArray(mRendererID);
	};
	void Unbind() {
		glBindVertexArray(0);
	};

	void AddVertexBuffer(VertexBuffer* buffer) {
		//Use this vertex array
		glBindVertexArray(mRendererID);

		//For this vertex buffer, we want to specify the layot
		//So we bind it
		buffer->Bind();

		//Verts
	
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
		glEnableVertexAttribArray(0);

		//Normals

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		//uvs																

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);
		//Unbinds ? 
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		mVertexBuffers.push_back(buffer);
	};
	void AddIndexBuffer(IndexBuffer* buffer) {
		//Use this vertex array
		glBindVertexArray(mRendererID);

		//For this vertex buffer, we want to specify the layot
		//So we bind it
		buffer->Bind();


		mIndexBuffer = buffer;
	};

	void SetID(uint32_t id) {
		mRendererID = id;
	}

	IndexBuffer* GetIndexBuffer() {
		return mIndexBuffer;
	}
private:
	uint32_t mRendererID = 0;
	std::vector<VertexBuffer*> mVertexBuffers;
	IndexBuffer* mIndexBuffer;
};
#pragma once
#include "Renderer.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <stdint.h>
class VertexBuffer {
public:
	VertexBuffer(float* vertices, uint32_t size) {
		//Creates the buffer
		glCreateBuffers(1, &mRendererID);
		//				We want an array, how many bytes, 
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	};

	void Bind() {
		glBindBuffer(GL_ARRAY_BUFFER, mRendererID); 
	}
	void Unbind()[
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	]
private:
	uint32_t mRendererID = 1;
};
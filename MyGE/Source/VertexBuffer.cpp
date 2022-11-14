#include "VertexBuffer.h"


VertexBuffer::VertexBuffer(float* vertices, uint32_t size) {
	//Creates the buffer
	glCreateBuffers(1, &mRendererID);
	//				We want an array, how many bytes, 
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}; 

void VertexBuffer::Bind() {
	glBindBuffer(GL_ARRAY_BUFFER, mRendererID);
}

void VertexBuffer::Unbind() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
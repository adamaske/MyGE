#pragma once
#include <stdint.h>
//Class for all vertex buffers
class VertexBuffer {
public:
	VertexBuffer(float* verts, size_t size);
	virtual ~VertexBuffer() { };

	virtual void Bind();
	virtual void Unbind();

	static VertexBuffer* Create(float* vertices, uint32_t size);
private:
	uint32_t mRendererID = 0;
};

class IndexBuffer {
public:
	virtual ~IndexBuffer() {};

	virtual void Bind();
	virtual void Unbind();

	static IndexBuffer* Create(uint32_t* indices, uint32_t size);
private:
	uint32_t mRendererID = 0;
};
#pragma once
#include <stdint.h>
//Class for all vertex buffers
class VertexBuffer {
public:
	VertexBuffer(float* verts, size_t size);
	virtual ~VertexBuffer() { };

	virtual void Bind();
	virtual void Unbind();

private:
	uint32_t mRendererID = 0;
};

class IndexBuffer {
public:
	IndexBuffer(uint32_t* indices, uint32_t count);
	virtual ~IndexBuffer() {};

	virtual void Bind();
	virtual void Unbind();

	uint32_t GetCount() { return mCount; };
private:
	uint32_t mRendererID = 0;
	uint32_t mCount;
};
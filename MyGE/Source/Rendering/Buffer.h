#pragma once
#include <stdint.h>
//Class for all vertex buffers
class VertexBuffer {
public:
	VertexBuffer(std::vector<Vertex> verts);
	VertexBuffer(std::vector<float> verts);
	VertexBuffer(float* verts, size_t size);
	virtual ~VertexBuffer() { };

	virtual void Bind();
	virtual void Unbind();

	float* mVerts;
	size_t mSize;
private:
	uint32_t mVBO = 0;
};

class IndexBuffer {
public:
	IndexBuffer(std::vector<uint32_t> inds);
	IndexBuffer(uint32_t* indices, uint32_t count);
	virtual ~IndexBuffer() {};

	virtual void Bind();
	virtual void Unbind();

	uint32_t* mIndices;
	size_t mSize;

	uint32_t GetCount() { return mCount; };
private:
	uint32_t mIBO = 0;
	uint32_t mCount;

	
};
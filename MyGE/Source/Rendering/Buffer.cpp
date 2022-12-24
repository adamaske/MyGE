#include "pch.h"

#include "Buffer.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Renderer.h"
VertexBuffer::VertexBuffer(std::vector<Vertex> verts)
{
	//We want a buffer in that renderer
	glGenBuffers(1, &mVBO);
	//
	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	//In that buffer we want an array, with the size of size and the floats of verts, which wont chagne 
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * verts.size(), &verts[0], GL_STATIC_DRAW);

}
VertexBuffer::VertexBuffer(std::vector<float> verts) {
	//We want a buffer in that renderer
	glGenBuffers(1, &mVBO);
	//
	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	//In that buffer we want an array, with the size of size and the floats of verts, which wont chagne 
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * verts.size(), &verts[0], GL_STATIC_DRAW);
}
VertexBuffer::VertexBuffer(float* verts, size_t size) {

	//We want a buffer in that renderer
	glGenBuffers(1, &mVBO);
	//
	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	//In that buffer we want an array, with the size of size and the floats of verts, which wont chagne 
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

	mVerts	= verts;
	mSize	= size;
}

void VertexBuffer::Bind()
{
	//We want to bind the buffer we created in mRenderer
	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
}

void VertexBuffer::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

IndexBuffer::IndexBuffer(std::vector<uint32_t> inds) : mCount(inds.size())
{
	glGenBuffers(1, &mIBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, inds.size() * sizeof(uint32_t), inds.data(), GL_STATIC_DRAW);
}

IndexBuffer::IndexBuffer(uint32_t* indices, uint32_t count) : mCount(count) {
	glGenBuffers(1, &mIBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);

	mIndices = indices;
	mSize = count;
};

void IndexBuffer::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);
}

void IndexBuffer::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

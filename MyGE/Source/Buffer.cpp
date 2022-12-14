#include "pch.h"

#include "Buffer.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Renderer.h"
VertexBuffer::VertexBuffer(float* verts, size_t size) {

	//We want a buffer in that renderer
	glGenBuffers(1, &mRendererID);
	//
	glBindBuffer(GL_ARRAY_BUFFER, mRendererID);
	//In that buffer we want an array, with the size of size and the floats of verts, which wont chagne 
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), &verts[0], GL_STATIC_DRAW);

	mVerts	= verts;
	mSize	= size;
}

void VertexBuffer::Bind()
{
	//We want to bind the buffer we created in mRenderer
	glBindBuffer(GL_ARRAY_BUFFER, mRendererID);
}

void VertexBuffer::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, mRendererID);
}

IndexBuffer::IndexBuffer(uint32_t* indices, uint32_t count) : mCount(count) {
	glGenBuffers(1, &mRendererID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mRendererID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);

	mIndices	= indices;
	mSize		= count;
};

void IndexBuffer::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mRendererID);
}

void IndexBuffer::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

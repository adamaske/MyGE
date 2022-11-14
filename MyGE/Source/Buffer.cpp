#include "Buffer.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
void VertexBuffer::Bind()
{
	glCreateBuffers(1, &mRendererID);
}

void VertexBuffer::Unbind()
{
}

VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
{

}

void IndexBuffer::Bind()
{

}

void IndexBuffer::Unbind()
{

}

IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size)
{

}

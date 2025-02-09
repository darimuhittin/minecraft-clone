#include "graphics/VertexBuffer.h"

VertexBuffer::VertexBuffer()
    : m_RendererID(0)
{
    glGenBuffers(1, &m_RendererID);
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &m_RendererID);
}

void VertexBuffer::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
}

void VertexBuffer::Unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::SetData(const void* data, unsigned int size, GLenum usage)
{
    Bind();
    glBufferData(GL_ARRAY_BUFFER, size, data, usage);
} 
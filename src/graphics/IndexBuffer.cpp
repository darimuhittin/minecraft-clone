#include "graphics/IndexBuffer.h"

IndexBuffer::IndexBuffer()
    : m_RendererID(0), m_Count(0)
{
    glGenBuffers(1, &m_RendererID);
}

IndexBuffer::~IndexBuffer()
{
    glDeleteBuffers(1, &m_RendererID);
}

void IndexBuffer::Bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
}

void IndexBuffer::Unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndexBuffer::SetData(const unsigned int* data, unsigned int count, GLenum usage)
{
    m_Count = count;
    Bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, usage);
}

void IndexBuffer::SetData(const std::vector<unsigned int>& data, GLenum usage)
{
    SetData(data.data(), static_cast<unsigned int>(data.size()), usage);
} 